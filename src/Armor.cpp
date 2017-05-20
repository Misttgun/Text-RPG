#include "EntityManager.h"
#include "Armor.h"

Armor::Armor(std::string id, std::string name, std::string description, int defense) : Item(id, name, description)
{
	this->defense = defense;
}

Armor::Armor(std::string id, Json &json, EntityManager* em) : Item(id, json, em)
{
	load(json, em);
}

void Armor::load(Json &json, EntityManager* em)
{
	defense = json["defense"].get<int>();

	return;
}