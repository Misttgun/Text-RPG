#pragma once

#include <list>
#include <utility>

#include "Json.hpp"
#include "EntityManager.h"


class Item;
class Weapon;
class Armor;

class Inventory
{
private:
	// The first element of the pair stores a pointer to the item in the EntityManager, and the second element stores the quantity of the item
	std::list<std::pair<Item*, int>> items;

	// Load the items of type T into the storage list from a Json file
	template<typename T>
	void load(Json &json, EntityManager* em);

	// Return a Json representation of all the items of type T
	template<typename T>
	Json jsonArray();

public:
	// Add an item to the inventory
	void add(Item* item, int count);

	// Remove the specified number of items from the inventory
	void remove(Item* item, int count);

	// Returns the count of the specified item
	int count(Item* item);
	template<typename T>
	int count(unsigned int n);

	// Returns the nth item in the storage list
	template<typename T>
	T* get(unsigned int n);

	// Output a list of the items onto stdout, formatted nicely and numbered if required
	template<typename T>
	int print(bool label = false);

	// Print the entire inventory. If the inventory is empty, then output "Nothing"
	int print(bool label = false);

	// Remove all items from the inventory
	void clear();

	// Merge the specified inventory with the current one
	void merge(Inventory* inventory);

	// Constructors
	Inventory(Json &json, EntityManager* em);
	Inventory() {}

	// Get a Json representation of the inventory
	Json getJson();

};