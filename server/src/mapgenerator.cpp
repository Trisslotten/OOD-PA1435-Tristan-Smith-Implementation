#include "mapgenerator.hpp"

#include "map.hpp"

void TestGenerator::setSeed(const std::string & seed)
{
	this->seed = seed;
}

void TestGenerator::generateMap(Map & map)
{
	
	for (int y = 0; y < map.getHeight(); y++)
	{
		for (int x = 0; x < map.getWidth(); x++)
		{
			/*
			if (x >= 3 && map.getWidth() - x - 1 >= 3 && y >= 3 && map.getWidth() - y - 1 >= 3)
			{
				if (x == 3 || map.getWidth() - x - 1 == 3 || y == 3 || map.getHeight() - y - 1 == 3)
				{
					map.setTileAt(x, y, TILE_WALL);
				}
				else
				{
					map.setTileAt(x, y, TILE_GROUND);
				}
			}
			else
			{
				map.setTileAt(x, y, TILE_NOTHING);
			}
			*/
			sf::Int8 asd = (sf::Int8)rand() % NUM_TILES;
			map.setTileAt(x, y, (Tile)asd);
		}
	}

}
