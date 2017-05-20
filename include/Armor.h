#pragma once

#include <string>

#include "Item.h"

class EntityManager;

class Armor : public Item
{
public:
	// Defense of the armor
	int defense;

	// Constructors
	Armor(std::string id, std::string name, std::string description, int defense);
	Armor(std::string id, Json &json, EntityManager* em);

	// Load the armor from the Json Value
	void load(Json &json, EntityManager* em);
};