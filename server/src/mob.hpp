#pragma once

#include "../../shared/definitions.hpp"

#include <SFML/Graphics.hpp>
#include <string>

class Mob
{
protected:
	ID id;
	std::string name;
	std::string description;
	char symbol;
	sf::Color color;
	int health, max_health;

	
	sf::Clock walk_timer;
	sf::Vector2i pos;
	sf::Vector2i vel;
	sf::Vector2i prev_vel;
public:

	Mob(ID _id);
	Mob() {}
	Mob(ID id,std::string name,std::string description, sf::Vector2i pos, int health, int max_health);

	void update();

	inline ID getID() const
	{
		return id;
	}
	inline std::string getName() const
	{
		return name;
	}
	inline std::string getDescription() const
	{
		return description;
	}
	inline char getSymbol() const
	{
		return symbol;
	}
	inline sf::Color getColor() const
	{
		return color;
	}
	inline int getHealth() const
	{
		return health;
	}
	inline int getMaxHealth()const
	{
		return max_health;
	}
	inline sf::Vector2i getPos()const
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
	inline void setVel(sf::Vector2i v)
	{
		vel = v;
	}
	inline void attack(unsigned int damage)
	{
		this->health -= damage;
	}
};
