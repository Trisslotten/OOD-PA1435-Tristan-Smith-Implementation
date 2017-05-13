#pragma once

#include "../../shared/definitions.hpp"

#include <SFML/Graphics.hpp>
#include <string>

class Mob
{
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
	inline sf::Color getColor()
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
	inline sf::Vector2i getPos()
	{
		return pos;	
	}
	inline void setID(ID _id)
	{
		id = _id;	
	}
	inline void setName(std::string n)
	{
		name = n;	
	}
	inline void setDescription(std::string desc)
	{
		description = desc;
	}
	inline void setSymbol(char sym)
	{
		symbol = sym;	
	}
	inline void setColor(sf::Color col)
	{
		color = col;	
	}
	inline void setHealth(int i)
	{
		health = i;	
	}
	inline void setMaxHealth(int max)
	{
		max_health = max;	
	}
	inline void setPos(sf::Vector2i p)
	{
		pos = p;	
	}
};
