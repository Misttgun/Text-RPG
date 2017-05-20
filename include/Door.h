#pragma once

#include <string>
#include <utility>

#include "Entity.h"

class Item;
class EntityManager;

class Door : public Entity
{
public:

	// Door description
	std::string description;

	// -1 is open, 0 is unlocked but closed and 1 is locked and needs key to open
	int locked;

	// If the player has the required key then they can unlock the door.
	Item* key;

	// A pair of Area ids connected by the door.
	std::pair<std::string, std::string> areas;

	Door(std::string id, std::string description, std::pair<std::string, std::string> areas, int locked, Item* key = nullptr);
	Door(std::string id, Json &json, EntityManager* mgr);

	void load(Json &json, EntityManager* mgr);
};