#pragma once

#include <string>
#include <cstdlib>

#include "Json.hpp"
#include "Entity.h"
#include "Inventory.h"

class Area;
class EntityManager;
class Weapon;
class Armor;
class Door;

class Creature : public Entity
{
public:

	// Name of the creature
	std::string name;

	// Creature stats
	int hp;
	int maxHp;
	int strength;
	int agility;
	double evasion;
	unsigned int xp;

	// Items that the creature possesses
	Inventory inventory;

	// Currently equipped weapon. nullptr denotes that no weapon is equipped
	Weapon* equippedWeapon;

	// Currently equipped armor.
	Armor* equippedArmor;

	// Area the creature resides in
	std::string currentArea;

	// Constructors
	Creature(std::string id, std::string name, int hp, int strength, int agility, double evasion, unsigned int xp);
	Creature(std::string id, Json &json, EntityManager* mgr);

	// Equip a weapon by setting the equipped weapon pointer.
	void equipWeapon(Weapon* weapon);

	// Equip the armor into it's correct slot
	void equipArmor(Armor* armor);

	// Convert internal area id into a pointer
	Area* getAreaPtr(EntityManager* mgr);

	// Attack the target creature, reducing their health if necessary
	int attack(Creature* target);

	// Go through a door
	// 0 = Door is locked, 1 = Door unlocked using key and 2 = Door is open
	int traverse(Door* door);

	// Create a JSON object containing the creature data
	virtual Json toJson();

	// Attempt to load all data from the JSON value
	virtual void load(Json &json, EntityManager* mgr);
};