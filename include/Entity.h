#pragma once

#include <string>

#include "Json.hpp"

using Json = nlohmann::json;

// Forward declaration to prevent multiple inclusion Entity need to know about EntityManager
class EntityManager;

class Entity
{
public:
	std::string id;

	Entity(const std::string id) { this->id = id; }

	// Destructor is virtual because all derived classes are treated as Entity by the EntityManager
	virtual ~Entity(){}

	// Pure virtual function to make the entity class an abstract class
	virtual void load(Json &json, EntityManager* manager) = 0;
};