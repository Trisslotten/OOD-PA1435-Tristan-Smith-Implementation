#include "map.hpp"

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

Tile Map::tileAt(sf::Vector2i pos)
{
	return tileAt(pos.x, pos.y);
}

Tile Map::tileAt(int x, int y)
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


