#pragma once

#include <string>

#include "Item.h"

class EntityManager;

class Weapon : public Item
{
public:
	// Damage of the weapon
	int damage;

	// Constructors
	Weapon(std::string id, std::string name, std::string description, int defense);
	Weapon(std::string id, Json &json, EntityManager* em);

	// Load the armor from the Json Value
	void load(Json &json, EntityManager* em);
};