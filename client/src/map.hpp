#pragma once

#include <vector>

#include <SFML/Network.hpp>
#include "../../shared/definitions.hpp"
#include "renderer.hpp"

class Map
{
	int width, height;
	// maybe later change to chunks or rooms?
	std::vector<Tile> tiles;

public:
	Map() {}

	void setSize(int _width, int _height);

	void render(Renderer& renderer, sf::Vector2i offset);

	Tile tileAt(sf::Vector2i pos);
	Tile tileAt(int x, int y);

	void setTileAt(sf::Vector2i pos, Tile tile);
	void setTileAt(int x, int y, Tile tile);

	inline int getWidth()
	{
		return width;
	}
	inline int getHeight()
	{
		return height;
	}

};