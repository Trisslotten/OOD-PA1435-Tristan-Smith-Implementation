#pragma once

#include "../../shared/definitions.hpp"

#include <SFML/Graphics.hpp>
#include <string>

class Mob
{
// TODO: change to protected or private
private:
	ID id;
	std::string name;
	std::string description;
	char symbol;
	sf::Color color;
	int health, max_health;

	sf::Vector2i pos;
public:
	inline ID getID()
	{
		return id;	
	}
	inline std::string getName()
	{
		return name;	
	}
	inline std::string getDescription()
	{
		return description;	
	}
	inline char getSymbol()
	{
		return symbol;	
	}
	inline sf::color getColor()
	{
		return color;	
	}
	inline int getHealth()
	{
		return health;	
	}
	inline int getMaxHealth()
	{
		return max_health;	
	}
	inline sf::vector2i getPos()
	{
		return pos;	
	}
};
