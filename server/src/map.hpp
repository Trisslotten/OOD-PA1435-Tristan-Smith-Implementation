#pragma once

#include <vector>

#include <SFML/Network.hpp>
#include "../../shared/definitions.hpp"

class Map
{
	int width, height;
	// maybe later change to chunks or rooms?
	std::vector<Tile> tiles;

public:
	Map(int _width, int _height);
	Map() = delete;

	sf::Int8 tileAt(sf::Vector2i pos) const;
	sf::Int8 tileAt(int x, int y) const;
	bool isWallAt(int x, int y);
	bool isGroundAt(int x, int y);
	bool isWallAt(sf::Vector2i pos);
	bool isGroundAt(sf::Vector2i pos);


	void setTileAt(sf::Vector2i pos, Tile tile);
	void setTileAt(int x, int y, Tile tile);

	inline int getWidth() const
	{
		return width;
	}
	inline int getHeight() const
	{
		return height;
	}

	void serializeChunk(sf::Packet& to_append, int x_start, int x_end, int y_start, int y_end) const;

	// old, do not use
	//void serialize(sf::Packet& to_append);

};