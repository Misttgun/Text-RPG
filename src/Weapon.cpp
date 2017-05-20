#include "EntityManager.h"
#include "Weapon.h"

Weapon::Weapon(std::string id, std::string name, std::string description, int damage) : Item(id, name, description)
{
	this->damage = damage;
}

Weapon::Weapon(std::string id, Json &json, EntityManager* em) : Item(id, json, em)
{
	load(json, em);
}

void Weapon::load(Json &json, EntityManager* em)
{
	damage = json["damage"].get<int>();

	return;
}