#pragma once

#include <string>
#include <map>

#include "Entity.h"

class EntityManager
{
private:
	// Map which keep a pointer to our different type of entities
	std::map<std::string, Entity*> data;

public:
	// Load the JSON file and determine which map to save the data to according to the type T
	template<typename T>
	void loadJSON(std::string filename);

	// Return the entity given by id
	template<typename T>
	T* getEntity(std::string id);

	// Constructor
	EntityManager();

	// Destructor
	~EntityManager();
};

// Convert a derived entity type to its id prefix (Item -> "item")
template<typename T>
std::string entityToString();
