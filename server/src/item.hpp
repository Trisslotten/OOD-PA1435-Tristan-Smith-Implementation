#pragma once
#include "../../shared/definitions.hpp"

#include <SFML/Graphics.hpp>
#include <string>

class Item
{
private:
	ID id;
	std::string name, description;
	sf::Color color;
	char symbol;
public:
	inline ID getItemId() { return id; }
	inline std::string getName() { return name; }
	inline std::string getDescription() { return description; }
	inline char getSymbol() { return symbol; }
	inline sf::Color getColor() { return color; }
};