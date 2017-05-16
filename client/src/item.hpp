#pragma once
#include "../../shared/definitions.hpp"
#include <SFML/Graphics.hpp>
#include <string>



class Item
{
private:
	ID id;
	std::string name, description;
	sf::Color color = sf::Color(255, 255, 255, 255);
	char symbol;
	sf::Vector2i last_ground_pos;
	unsigned int damage = 0;
public:
	inline ID getItemId() { return id; }
	inline std::string getName() { return name; }
	inline std::string getDescription() { return description; }
	inline char getSymbol() { return symbol; }
	inline sf::Color getColor() { return color; }
	inline sf::Vector2i getPos() { return last_ground_pos; }
	inline void setPos(sf::Vector2i pos) { this->last_ground_pos = pos; }

	Item();
	Item(ID id, std::string name, std::string description, char symbol, sf::Vector2i pos, sf::Color color, unsigned int damage = 10);

};