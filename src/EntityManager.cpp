#include <fstream>

#include "EntityManager.h"
#include "Json.hpp"
#include "Item.h"
#include "Armor.h"
#include "Weapon.h"
#include "Door.h"
#include "Area.h"
#include "Creature.h"

EntityManager::EntityManager() {}

template<class T>
void EntityManager::loadJSON(const std::string filename)
{
	// Create a Json and load the JSONFile 
	Json json;
	std::ifstream i(filename.c_str());
	i >> json;

	// Iterate over the Json objects
	for (auto it = json.begin(); it != json.end(); it++)
	{
		// Extract the key in the Json object
		std::string key = it.key();
		// Dynamic cast to convert the resulting pointer into an Entity pointer and add it to the data map 
		data[key] = dynamic_cast<Entity*>(new T(key, it.value(), this));
	}
}

template<class T>
T* EntityManager::getEntity(const std::string id)
{
	/* The id prefix should match to the type T, so take the first characters of the id
	up to the length of the prefix and compare the two */
	if (id.substr(0, entityToString<T>().size()) == entityToString<T>())
		return dynamic_cast<T*>(data.at(id));
	else
		return nullptr;
}

EntityManager::~EntityManager()
{
	// Deallocates all the memory allocated by the "new" keyword in loadJson
	for (auto& entity : data)
	{
		delete entity.second;
		entity.second = nullptr;
	}
}

// Template specialisations
template<> std::string entityToString<Item>() { return "item"; }
template<> std::string entityToString<Armor>() { return "armor"; }
template<> std::string entityToString<Weapon>() { return "weapon"; }
template<> std::string entityToString<Area>() { return "area"; }
template<> std::string entityToString<Door>() { return "door"; }
template<> std::string entityToString<Creature>() { return "creature"; }

// Template instantiation
template void EntityManager::loadJSON<Item>(std::string);
template void EntityManager::loadJSON<Armor>(std::string);
template void EntityManager::loadJSON<Weapon>(std::string);
template void EntityManager::loadJSON<Area>(std::string);
template void EntityManager::loadJSON<Door>(std::string);
template void EntityManager::loadJSON<Creature>(std::string);

template Item* EntityManager::getEntity<Item>(std::string);
template Armor* EntityManager::getEntity<Armor>(std::string);
template Weapon* EntityManager::getEntity<Weapon>(std::string);
template Area* EntityManager::getEntity<Area>(std::string);
template Door* EntityManager::getEntity<Door>(std::string);
template Creature* EntityManager::getEntity<Creature>(std::string);