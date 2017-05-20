#include <vector>
#include <string>

#include "Area.h"
#include "Door.h"
#include "Entity.h"
#include "Inventory.h"
#include "Dialogue.h"
#include "EntityManager.h"

Area::Area(std::string id, Dialogue dialogue, Inventory items, std::vector<Creature*> creatures) : Entity(id)
{
	this->dialogue = dialogue;
	this->items = items;
	for (auto creature : creatures)
	{
		this->creatures.push_back(*creature);
	}
}

Area::Area(std::string id, Json &json, EntityManager* mgr) : Entity(id)
{
	this->load(json, mgr);
}

void Area::load(Json &json, EntityManager* mgr)
{
	// Build the dialogue
	// This is an optional parameter because it will not be saved when the area is modified
	if (json.find("dialogue") != json.end())
		dialogue = Dialogue(json["dialogue"]);

	// Build the inventory
	items = Inventory(json["inventory"], mgr);

	// Build the creature list
	creatures.clear();
	for (auto creature : json["creatures"])
	{
		// Create a new creature instance indentical to the version in the entity manager
		Creature c(*mgr->getEntity<Creature>(creature.get<std::string>()));
		creatures.push_back(c);
	}

	// Attach doors
	if (json.find("doors") != json.end())
	{
		doors.clear();
		for (auto door : json["doors"])
		{
			Door* d = nullptr;
			// Each door is either an array of the type [id, locked] or
			// a single id string.
			if (door.is_string())
			{
				d = mgr->getEntity<Door>(door.get<std::string>());
			}
			else
			{
				d = mgr->getEntity<Door>(door[0].get<std::string>());
				d->locked = door[1].get<int>();
			}
			doors.push_back(d);
		}
	}

	return;
}

Json Area::getJson()
{
	Json object;

	// Save the inventory
	object["inventory"] = items.getJson();

	// Save the creatures
	Json array;
	for (auto creature : creatures)
	{
		array.push_back(creature.id);
	}
	object["creatures"] = array;

	// Save the doors
	array.clear();
	for (auto door : doors)
	{
		Json d;
		d.push_back(door->id);
		d.push_back(door->locked);
		array.push_back(d);
	}
	object["doors"] = array;

	return object;
}