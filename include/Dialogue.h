#pragma once

#include <string>
#include <vector>
#include <iostream>

#include "Json.hpp"

using Json = nlohmann::json;

class Dialogue
{
private:
	// Initial piece of information that the dialogue displays
	std::string description;

	// A vector of choices that will be outputted. No nubering necessary, the dialogue does that automatically
	std::vector<std::string> choices;

public:
	// Run the dialogue
	int activate()
	{
		// Outup the information
		std::cout << description << std::endl;

		// Output the number of choices
		for (int i = 0; i < choices.size(); i++)
		{
			std::cout << i + 1 << ": " << choices[i] << std::endl;
		}

		// Read input from stream
		int userInput = -1;
		while (true)
		{
			std::cin >> userInput;
			// 'Valid' means within the range of numbers outputted
			if (userInput >= 0 && userInput <= choices.size())
			{
				return userInput;
			}
		}
	}

	// Constructor
	Dialogue(std::string description, std::vector<std::string> choices)
	{
		this->description = description;
		this->choices = choices;
	}

	// Create a dialogue from a JSON value
	Dialogue(Json &json)
	{
		description = json["description"].get<std::string>();
		for (auto choice : json["choices"])
			choices.push_back(choice.get<std::string>());
	}

	Dialogue() {}

	void addChoice(std::string choice)
	{
		choices.push_back(choice);
	}

	unsigned int size()
	{
		return choices.size();
	}
};