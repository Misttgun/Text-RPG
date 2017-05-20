#include <unordered_set>
#include <cmath>
#include <fstream>

#include "Area.h"
#include "Player.h"
#include "Creature.h"
#include "EntityManager.h"

Player::Player(std::string name, int hp, int strength, int agility, double evasion, unsigned int xp, unsigned int level, std::string className) : Creature("player", name, hp, strength, agility, evasion, xp)
{
	this->level = level;
	this->className = className;
}

Player::Player() : Player::Player("", 0, 0, 0, 0.0, 0, 1, "nullid"){}

Player::Player(Json &saveData, Json &areaData, EntityManager* mgr) : Player::Player()
{
	load(saveData, mgr);
	loadArea(areaData, mgr);
}

Json Player::toJson()
{
	Json object = Creature::toJson();

	object["className"] = className;
	object["level"] = int(level);

	return object;
}

void Player::save(EntityManager* mgr)
{
	// Construct JSON representation of the player and save it to a file
	Json player(this->toJson());
	std::ofstream out1(("data/" + name + ".json").c_str());
	out1 << std::setw(4) << player << std::endl;
	out1.close();

	// Construct a JSON object containing the areas the player has visited 
	Json object;
	for (auto area : visitedAreas)
	{
		object[area] = mgr->getEntity<Area>(area)->getJson();
	}

	// Write the object to a file similar to the player data
	Json area(object);
	std::ofstream out2(("data/" + name + "_areas.json").c_str());
	out2 << std::setw(4) << area << std::endl;
	out2.close();

	return;
}

void Player::load(Json &saveData, EntityManager* mgr)
{
	// Load data shared with Creature
	Creature::load(saveData, mgr);

	// Load optional variables
	className = saveData["className"].get<std::string>();
	level = saveData["level"].get<int>();

	return;
}

void Player::loadArea(Json &areaData, EntityManager* mgr)
{
	// Load the area
	for(auto it = areaData.begin(); it != areaData.end(); it++)
	{
		std::string key = it.key();
		mgr->getEntity<Area>(key)->load(it.value(), mgr);
		visitedAreas.insert(key);
	}

	return;
}

unsigned int Player::xpToLevel(unsigned int level)
{
	return (unsigned int)(1.5 * std::pow(this->level, 3));
}

bool Player::levelUp()
{
	// Can't level up if there's not enough experience
	if (xp < xpToLevel(level + 1))
	{
		return false;
	}

	// Advance to the next level
	++level;

	// Variables to keep track of stat changes, and their associated multipliers, which depend on the class.
	unsigned int statIncreases[3] = { 0, 0, 0 };
	float statMultipliers[3] = { 0, 0, 0 };
	statMultipliers[0] = 13.0;
	statMultipliers[1] = className == "Fighter" ? 8.0 : 6.0;
	statMultipliers[2] = className == "Rogue" ? 8.0 : 6.0;

	// Compute the stat increases for each stat
	for (int i = 0; i < 3; ++i)
	{
		float base = std::tanh(level / 30.0) * ((level % 2) + 1);
		statIncreases[i] += int(1 + statMultipliers[i] * base);
	}

	// Adjust all of the stats accordingly
	hp += statIncreases[0];
	maxHp += statIncreases[0];
	strength += statIncreases[1];
	agility += statIncreases[2];

	// Tell the user that they grew a level, what the increases were and what their stats are now
	std::cout << name << " grew to level " << level << "!\n";
	std::cout << "Health   +" << statIncreases[0] << " -> " << maxHp << std::endl;
	std::cout << "Strength +" << statIncreases[1] << " -> " << strength << std::endl;
	std::cout << "Agility  +" << statIncreases[2] << " -> " << agility << std::endl;
	std::cout << "----------------\n";

	return true;
}