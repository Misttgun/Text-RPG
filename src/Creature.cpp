#include <string>
#include <cstdlib>

#include "Creature.h"
#include "Entity.h"
#include "Inventory.h"
#include "Weapon.h"
#include "Armor.h"
#include "Door.h"
#include "Area.h"
#include "EntityManager.h"

Creature::Creature(std::string id, std::string name, int hp, int strength, int agility, double evasion, unsigned int xp) : Entity(id)
{
	this->name = name;
	this->hp = hp;
	this->maxHp = hp;
	this->strength = strength;
	this->agility = agility;
	this->evasion = evasion;
	this->equippedArmor = nullptr;
	this->equippedWeapon = nullptr;
	this->xp = xp;
}

Creature::Creature(std::string id, Json &json, EntityManager* mgr) : Creature(id, "", 0, 0, 0, 0, 0)
{
	this->load(json, mgr);
}

void Creature::equipWeapon(Weapon* weapon)
{
	this->equippedWeapon = weapon;

	return;
}

void Creature::equipArmor(Armor* armor)
{
	this->equippedArmor = armor;

	return;
}

Area* Creature::getAreaPtr(EntityManager* mgr)
{
	return mgr->getEntity<Area>(currentArea);
}

int Creature::attack(Creature* target)
{
	// Damage done
	int damage = 0;

	if (double(std::rand()) / RAND_MAX  > target->evasion)
	{
		// Calculate attack based on strength and weapon damage
		int attack = this->strength + (this->equippedWeapon == nullptr ? 0 : this->equippedWeapon->damage);

		// Calculate defense based on agility and armor defense
		int defense = target->agility + (target->equippedArmor == nullptr ? 0 : target->equippedArmor->defense);

		// 1/32 chance of a critical hit
		if (std::rand() % 32 == 0)
		{
			// Ignore defense and do damage in range [attack/2, attack]
			damage = attack / 2 + std::rand() % (attack / 2 + 1);
		}
		else
		{
			// Normal hit so factor in defense
			int baseDamage = attack - defense / 2;

			// Do damage in range [baseDamage/4, baseDamage/2]
			damage = baseDamage / 4 + std::rand() % (baseDamage / 4 + 1);

			// If the damage is zero then have a 50% chance to do 1 damage
			if (damage < 1)
			{
				damage = std::rand() % 2;
			}
		}
		// Damage the target
		target->hp -= damage;
	}

	return damage;
}

int Creature::traverse(Door* door)
{
	int flag = 2;
	// Open the door if it is shut
	if (door->locked == 0)
	{
		door->locked = -1;
		flag = 2;
	}
	else if (door->locked > 0)
	{
		// Unlock and open the door if the creature has the key
		if (this->inventory.count(door->key))
		{
			door->locked = -1;
			flag = 1;
		}
		else
		{
			return 0;
		}
	}
	if (door->areas.first == currentArea)
	{
		currentArea = door->areas.second;
	}
	else if (door->areas.second == currentArea)
	{
		currentArea = door->areas.first;
	}

	return flag;
}

Json Creature::toJson()
{
	Json object;
	object["name"] = name;
	object["hp"] = hp;
	object["hp_max"] = maxHp;
	object["strength"] = strength;
	object["agility"] = agility;
	object["evasion"] = evasion;
	object["xp"] = int(xp);
	object["inventory"] = inventory.getJson();
	object["equipped_weapon"] = (equippedWeapon == nullptr ? "nullptr" : equippedWeapon->id);
	object["equipped_armor"] = (equippedArmor == nullptr ? "nullptr" : equippedArmor->id);

	return object;
}

void Creature::load(Json &json, EntityManager* mgr)
{
	name = json["name"].get<std::string>();
	hp = json["hp"].get<int>();
	if (json.find("hp_max") != json.end())
	{
		maxHp = json["hp_max"].get<int>();
	}
	else
	{
		maxHp = hp;
	}
	strength = json["strength"].get<int>();
	agility = json["agility"].get<int>();
	evasion = json["evasion"].get<double>();
	xp = json["xp"].get<int>();

	if (json.find("inventory") != json.end())
	{
		inventory = Inventory(json["inventory"], mgr);
	}
	if (json.find("equipped_weapon") != json.end())
	{
		std::string equippedWeaponName = json["equipped_weapon"].get<std::string>();
		equippedWeapon = (equippedWeaponName == "nullptr" ? nullptr : mgr->getEntity<Weapon>(equippedWeaponName));
	}
	if (json.find("equipped_armor") != json.end())
	{
		std::string equippedArmorName = json["equipped_armor"].get<std::string>();
		equippedArmor = (equippedArmorName == "nullptr" ? nullptr : mgr->getEntity<Armor>(equippedArmorName));
	}

	return;
}