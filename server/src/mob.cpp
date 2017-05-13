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