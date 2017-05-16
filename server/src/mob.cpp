#include "mob.hpp"

Mob::Mob(ID id)
{
	this->id = id;
	this->color = sf::Color(255, 255, 255, 255);
	this->name = "unnamed";
	this->description = "non-descriptive";
	this->health = 100;
	this->max_health = 100;
	this->pos = sf::Vector2i(1, 1);
	this->symbol = '#';
}

Mob::Mob(ID id,std::string name, std::string description, sf::Vector2i pos, int health, int max_health)
{
	this->id = id;
	this->color = sf::Color(255, 255, 255, 255);
	this->name = name;
	this->description = description;
	this->health = health;
	this->max_health = max_health;
	this->pos = pos;
	this->symbol = '#';
}

void Mob::update()
{
	pos += vel;
	vel = sf::Vector2i();

	/*
	if (prev_vel.x == 0 && prev_vel.y == 0)
	{
		walk_timer.restart();
	}

	sf::Time t = walk_timer.getElapsedTime();
	prev_vel = vel;
	if (t < sf::seconds(0.01) || t > sf::seconds(0.2))
	{
		pos += vel;
		vel = sf::Vector2i();
	}
	*/
}
