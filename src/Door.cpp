#include <string>
#include <utility>

#include "Door.h"
#include "Item.h"
#include "Entity.h"
#include "EntityManager.h"

Door::Door(std::string id, std::string description, std::pair<std::string, std::string> areas, int locked, Item* key) : Entity(id)
{
	this->description = description;
	this->areas = areas;
	this->locked = locked;
	this->key = key;
}

Door::Door(std::string id, Json &json, EntityManager* mgr) : Entity(id)
{
	load(json, mgr);
}

void Door::load(Json &json, EntityManager* mgr)
{
	description = json["description"].get<std::string>();
	locked = json["locked"].get<int>();
	if (json.find("key") != json.end())
	{
		key = mgr->getEntity<Item>(json["key"].get<std::string>());
	}

	Json array = json["areas"];
	if (array.size() == 2)
	{
		areas.first = array[0].get<std::string>();
		areas.second = array[1].get<std::string>();
	}

	return;
}