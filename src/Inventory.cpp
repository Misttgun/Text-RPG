#include <string>
#include <iostream>

#include "Inventory.h"
#include "Item.h"
#include "Weapon.h"
#include "Armor.h"

Inventory::Inventory(Json &json, EntityManager* em)
{
	load<Item>(json["items"], em);
	load<Armor>(json["armors"], em);
	load<Weapon>(json["weapons"], em);
}

template<typename T>
void Inventory::load(Json &json, EntityManager* em)
{
	for (auto item : json)
	{
			Json temp = item;
			std::string itemId = temp[0];
			int quantity = temp[1];
			items.push_back(std::make_pair(em->getEntity<T>(itemId), quantity));
	}
}

template<typename T>
Json Inventory::jsonArray()
{
	Json array;
	for (auto item : items)
	{
		// Skip if the id does not match to the type T
		if (item.first->id.substr(0, entityToString<T>().size()) != entityToString<T>())
			continue;
		// Otherwise add the item to the array
		Json pair;
		pair.push_back(item.first->id);
		pair.push_back(item.second);
		array.push_back(pair);
	}

	return array;
}

Json Inventory::getJson()
{
	Json object;
	object["items"] = jsonArray<Item>();
	object["weapons"] = jsonArray<Weapon>();
	object["armors"] = jsonArray<Armor>();

	return object;
}

void Inventory::add(Item* item, int count)
{
	for (auto &it : items)
	{
		if (it.first->id == item->id)
		{
			it.second += count;
			return;
		}
	}
	items.push_back(std::make_pair(item, count));
}

void Inventory::remove(Item* item, int count)
{
	for (auto it = items.begin(); it != items.end(); it++)
	{
		if ((*it).first->id == item->id)
		{
			(*it).second -= count;
			if ((*it).second < 1) items.erase(it);
			return;
		}
	}
}

template<typename T>
T* Inventory::get(unsigned int n)
{
	// Using a list so we must step through n times from the start
	unsigned int i = 0;
	auto it = items.begin();
	for (; it != items.end(); it++)
	{
		// Skip if the id does not match to the type T
		if ((*it).first->id.substr(0, entityToString<T>().size()) != entityToString<T>())
			continue;
		if (i++ == n) break;
	}

	if (it != items.end())
		return dynamic_cast<T*>((*it).first);
	else
		return nullptr;
}

int Inventory::count(Item* item)
{
	for (auto it : items)
	{
		if (it.first->id == item->id)
			return it.second;
	}
	return 0;
}

template<typename T>
int Inventory::count(unsigned int n)
{
	return count(get<T>(n));
}

template<typename T>
int Inventory::print(bool label)
{
	unsigned int i = 1;

	for (auto it : items)
	{
		// Skip if the id does not match to the type T
		if (it.first->id.substr(0, entityToString<T>().size()) != entityToString<T>())
			continue;

		// Number the items if asked
		if (label) std::cout << i++ << ": ";

		// Outpout the item name quantity and description, e.g. Gold Piece (29) - Glimmering discs of wealth
		std::cout << it.first->name << " (" << it.second << ") - ";
		std::cout << it.first->description << std::endl;
	}

	// Return the number of items printed
	return items.size();
}

// Overload of print to print all items when the template argument is empty
int Inventory::print(bool label)
{
	unsigned int i = 0;
	if (items.empty())
	{
		std::cout << "Nothing" << std::endl;
	}
	else
	{
		i += print<Item>(label);
		i += print<Armor>(label);
		i += print<Weapon>(label);
	}

	return i;
}

void Inventory::clear()
{
	items.clear();
}

void Inventory::merge(Inventory* inventory)
{
	// You can't merge an inventory with itself
	if (inventory == this) return;

	// Loop through the items to be added, and add them
	for (auto it : inventory->items)
	{
		add(it.first, it.second);
	}

	return;
}

// Template instantiations
template void Inventory::load<Item>(Json&, EntityManager*);
template void Inventory::load<Weapon>(Json&, EntityManager*);
template void Inventory::load<Armor>(Json&, EntityManager*);

template Json Inventory::jsonArray<Item>();
template Json Inventory::jsonArray<Weapon>();
template Json Inventory::jsonArray<Armor>();

template int Inventory::count<Item>(unsigned int);
template int Inventory::count<Weapon>(unsigned int);
template int Inventory::count<Armor>(unsigned int);

template Item* Inventory::get<Item>(unsigned int);
template Weapon* Inventory::get<Weapon>(unsigned int);
template Armor* Inventory::get<Armor>(unsigned int);

template int Inventory::print<Item>(bool);
template int Inventory::print<Weapon>(bool);
template int Inventory::print<Armor>(bool);