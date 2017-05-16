#include "map.hpp"

#include <iostream>

Map::Map(int _width, int _height)
{
	width = _width;
	height = _height;
	tiles.resize(width*height);
	for (auto&& t : tiles)
	{
		t = TILE_NOTHING;
	}
}

sf::Int8 Map::tileAt(sf::Vector2i pos) const
{
	return tileAt(pos.x, pos.y);
}

sf::Int8 Map::tileAt(int x, int y) const
{
	if (x < 0 || x >= width || y < 0 || y >= height)
	{
		return TILE_NOTHING;
	}
	else
	{
		return tiles[x + y*width];
	}
}

void Map::setTileAt(sf::Vector2i pos, Tile tile)
{
	setTileAt(pos.x, pos.y, tile);
}

void Map::setTileAt(int x, int y, Tile tile)
{
	if (x >= 0 && x < width && y >= 0 && y < height)
		tiles[x + y*width] = tile;
}

void Map::serializeChunk(sf::Packet & to_append, int x_start, int x_end, int y_start, int y_end) const
{
	to_append << x_start << x_end << y_start << y_end;
	for (int y = y_start; y < y_end; y++)
	{
		for (int x = x_start; x < x_end; x++)
		{
			to_append << tileAt(x, y);
		}
	}
}
bool Map::isWallAt(int x, int y)
{
	sf::Int8 t = tileAt(x, y);
	if (t == TILE_WALL)
		return true;
	else
		return false;
}
bool Map::isGroundAt(int x, int y)
{
	sf::Int8 t = tileAt(x, y);
	if (t == TILE_GROUND)
		return true;
	else
		return false;
}
bool Map::isWallAt(sf::Vector2i pos)
{
	sf::Int8 t = tileAt(pos);
	if (t == TILE_WALL)
		return true;
	else
		return false;
}
bool Map::isGroundAt(sf::Vector2i pos)
{
	sf::Int8 t = tileAt(pos);
	if (t == TILE_GROUND)
		return true;
	else
		return false;
}

/*
void Map::serialize(sf::Packet & to_append)
{
	to_append << width << height;
	for (auto t : tiles)
	{
		to_append << (sf::Int8)t;
	}
}
*/

