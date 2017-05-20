#pragma once

#include <vector>
#include <string>

#include "Json.hpp"
#include "Entity.h"
#include "Inventory.h"
#include "Dialogue.h"
#include "Creature.h"

class EntityManager;
class Door;

class Area : public Entity
{
public:

	// Dialogue is run whenever the area is entered
	Dialogue dialogue;

	// Items contained within the area.
	Inventory items;

	// Links between rooms. Every door should have this as one of its area pointers
	std::vector<Door*> doors;
	
	// Creatures contained within the area. Not pointers because we want unique instances of the creatures
	std::vector<Creature> creatures;

	// Constructors
	Area(std::string id, Dialogue dialogue, Inventory items, std::vector<Creature*> creatures);
	Area(std::string id, Json &json, EntityManager* mgr);

	// Load the area from the given Json value
	void load(Json &json, EntityManager* mgr);

	// Return a Json object representing the area
	Json getJson();
};