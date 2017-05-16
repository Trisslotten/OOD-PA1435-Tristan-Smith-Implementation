#include "map.hpp"




void Map::setSize(int _width, int _height)
{
	width = _width;
	height = _height;
	tiles.resize(width*height);
}

void Map::render(Renderer & renderer, sf::Vector2i offset)
{
	sf::Vector2i size = renderer.getScreenSizeTiles();

	sf::Vector2i start = offset;
	sf::Vector2i end = offset + size;

	for(int y = start.y; y < end.y; y++) {
		for (int x = start.x; x < end.x; x++)
		{
			char symbol = 0;
			switch (tileAt(x, y))
			{
			case TILE_GROUND:
				symbol = '.';
				break;
			case TILE_WALL:
				symbol = '#';
				break;
			}
			sf::Vector2i pos(x, y);
			renderer.drawChar(pos - offset, symbol, sf::Color(125, 125, 125));
		}
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

bool Map::isWallAt(int x, int y)
{
	Tile t = tileAt(x, y);
	if (t == TILE_WALL)
		return true;
	else
		return false;
}
bool Map::isGroundAt(int x, int y)
{
	Tile t = tileAt(x, y);
	if (t == TILE_GROUND)
		return true;
	else
		return false;
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