#include "map.hpp"




void Map::setSize(int _width, int _height)
{
	width = _width;
	height = _height;
	tiles.resize(width*height);
}

void Map::render(Renderer & renderer, sf::Vector2i offset)
{
	for (int i = 0; i < width*height; i++)
	{
		int x = i % width;
		int y = i / width;
		char symbol = 0;
		switch (tiles[i])
		{
		case TILE_GROUND:
			symbol = '.';
			break;
		case TILE_WALL:
			symbol = '#';
			break;
		}
		sf::Vector2i pos(x, y);
		renderer.drawChar(pos - offset, symbol, sf::Color(125,125,125));
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