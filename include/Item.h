#pragma once

#include "Entity.h"

class EntityManager;

class Item : public Entity
{
public:
	// Name and description of the item
	std::string name;
	std::string description;

	//Constructor
	Item(std::string id, std::string name, std::string description);
	Item(std::string id, Json &json, EntityManager* em);

	// Load the item information from the Json Value
	virtual void load(Json &json, EntityManager* em);
};
