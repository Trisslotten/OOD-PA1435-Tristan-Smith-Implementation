#include "item.hpp"

Item::Item()
{
	id = 0;
	name = "unknown";
	description = "none";
	symbol = '#';
	last_ground_pos = sf::Vector2i(0, 0);
}

Item::Item(ID id, std::string name, std::string description, char symbol, sf::Vector2i pos, sf::Color color)
{
	this->id = id; this->name = name; this->description = description; this->symbol = symbol; this->last_ground_pos = pos;
	this->color = color;
}