#include "map.hpp"




void Map::setSize(int _width, int _height)
{
	width = _width;
	height = _height;
	tiles.resize(width*height);
}


unsigned char Map::getWallSymbol(const Renderer& renderer, int x, int y)
{
	bool left = false, right = false, top = false, bottom = false;
	left =		tileAt(x - 1, y) == TILE_WALL || tileAt(x - 1, y) == TILE_DOOR;
	right =		tileAt(x + 1, y) == TILE_WALL || tileAt(x + 1, y) == TILE_DOOR;
	top =		tileAt(x, y - 1) == TILE_WALL || tileAt(x, y - 1) == TILE_DOOR;
	bottom =	tileAt(x, y + 1) == TILE_WALL || tileAt(x, y + 1) == TILE_DOOR;
	if (left && right && top && bottom)
		return renderer.tileAt(14, 12);
	if (!left && right && top && bottom)
		return renderer.tileAt(12, 12);
	if (left && !right && top && bottom)
		return renderer.tileAt(9, 11);
	if (!left && !right && top && bottom)
		return renderer.tileAt(10, 11);
	if (left && right && !top && bottom)
		return renderer.tileAt(11, 12);
	if (!left && right && !top && bottom)
		return renderer.tileAt(9, 12);
	if (left && !right && !top && bottom)
		return renderer.tileAt(11, 11);
	if (!left && !right && !top && bottom)
		return renderer.tileAt(10, 11);

	if (left && right && top && !bottom)
		return renderer.tileAt(10, 12);
	if (!left && right && top && !bottom)
		return renderer.tileAt(8, 12);
	if (left && !right && top && !bottom)
		return renderer.tileAt(12, 11);
	if (!left && !right && top && !bottom)
		return renderer.tileAt(10, 11);
	if (left && right && !top && !bottom)
		return renderer.tileAt(13, 12);
	if (!left && right && !top && !bottom)
		return renderer.tileAt(13, 12);
	if (left && !right && !top && !bottom)
		return renderer.tileAt(13, 12);
	if (!left && !right && !top && !bottom)
		return '#';

	return '#';
}

void Map::render(Renderer & renderer, sf::Vector2i offset)
{
	sf::Vector2i size = renderer.getScreenSizeTiles();

	sf::Vector2i start = offset;
	sf::Vector2i end = offset + size;

	for(int y = start.y; y < end.y; y++) {
		for (int x = start.x; x < end.x; x++)
		{
			unsigned char symbol = 0;
			switch (tileAt(x, y))
			{
			case TILE_INDOOR_GROUND:
				symbol = (unsigned char)11 * 16;
				break;
			case TILE_GROUND:
				symbol = '.';
				break;
			case TILE_WALL:
				symbol = getWallSymbol(renderer, x, y);
				break;
			case TILE_DOOR:
				symbol = '|';
				break;
			case TILE_STAIRS_UP:
				symbol = '^';
				break;
			case TILE_STAIRS_DOWN:
				symbol = 'v';
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