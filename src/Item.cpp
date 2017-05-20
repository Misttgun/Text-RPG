#include "Item.h"
#include "EntityManager.h"

Item::Item(std::string id, std::string name, std::string description) : Entity(id)
{
	this->name = name;
	this->description = description;
}

Item::Item(std::string id, Json &json, EntityManager* em) : Entity(id)
{
	// Use the load function to create the Item from Json
	load(json, em);
}

void Item::load(Json &json, EntityManager* em)
{
	// Parse the Json to an Item
	name = json.at("name").get<std::string>();
	description = json.at("description").get<std::string>();

	return;
}


