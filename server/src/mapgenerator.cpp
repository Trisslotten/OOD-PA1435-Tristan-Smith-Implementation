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
void LevelGenerator::setSeed(const std::string & seed)
{
	this->seed = seed;
}
void LevelGenerator::generateMap(Map & map) {
	srand(time(NULL));

	int rooms = (rand() % 3)+2;
	std::vector<sf::Vector2i> points;
	int attempts=0;
	for (int i = 0; i < rooms && attempts < 100; i++) {

		int height = (rand() % 15) + 5;
		int width = (rand() % 15) + 5;

		int xPos = 1 + rand()%(map.getWidth() - width-3);
		int yPos = 1 + rand() % (map.getHeight() - height-3);

		if (checkRoomSpot(map, xPos, yPos, width, height)) {
			generateRoom(map, xPos, yPos, width, height);
			points.push_back(sf::Vector2i(xPos + width/2, yPos + height/2));
		}
		else {
			i--;
			attempts++;
		}
	}

	//add up/down stairs to access new levels of the dungeon
	while (true) {//shit code
		int stairsX = rand() % map.getWidth();
		int stairsY = rand() % map.getHeight();
		if (map.tileAt(stairsX, stairsY) == TILE_INDOOR_GROUND) {
			map.setTileAt(stairsX, stairsY, TILE_STAIRS_DOWN);
			break;
		}
	}
	while (true) {
		int stairsX = rand() % map.getWidth();
		int stairsY = rand() % map.getHeight();
		if (map.tileAt(stairsX, stairsY) == TILE_INDOOR_GROUND) {
			map.setTileAt(stairsX, stairsY, TILE_STAIRS_UP);
			break;
		}
	}
	//connect rooms so that players may progress
	for (int i = 0; i < points.size(); i++) {
		int x1 = points.at(i).x;
		int y1 = points.at(i).y;
		for (int j = i + 1; j < points.size(); j++) {
			bool insideWall = false;
			int x2 = points.at(j).x;
			int y2 = points.at(j).y;
			int attempts = 0;
			while ((x2 != x1 || y2 != y1) && attempts < 1000) {//stepper, moving FROM p2 TO p1
				bool dir = rand() % 2;

				int oldX2 = x2;
				int oldY2 = y2;

				if (dir) {//true = left/right
					if (x2 < x1) {
						x2++;
					}
					else {
						x2--;
					}
				}
				else {//false = up/down
					if (y2 < y1) {
						y2++;
					}
					else {
						y2--;
					}
				}
				if (map.tileAt(sf::Vector2i(x2, y2)) != TILE_WALL && map.tileAt(sf::Vector2i(x2, y2)) != TILE_DOOR) {
					insideWall = false;
				}
				if (insideWall) {
					x2 = oldX2;
					y2 = oldY2;
				}
				if (map.tileAt(sf::Vector2i(x2, y2)) == TILE_NOTHING) {
					map.setTileAt(x2, y2, TILE_GROUND);
				}
				if (map.tileAt(sf::Vector2i(x2, y2)) == TILE_WALL && !insideWall) {
					map.setTileAt(x2, y2, TILE_DOOR);
					insideWall = true;
				}
				attempts++;
			}
		}
		points.pop_back();
	}

	//finalize, reset generator-only values
	for (int y = 0; y < map.getHeight(); y++) {//fill code
		for (int x = 0; x < map.getWidth(); x++) {
			if (map.tileAt(sf::Vector2i(x, y)) == TILE_INDOOR_GROUND) {
				map.setTileAt(sf::Vector2i(x, y), TILE_GROUND);
			}
		}
	}

	std::cout << points.size() << std::endl;
}
bool LevelGenerator::checkRoomSpot(Map& map, int xPos, int yPos, int width, int height) {//check if you can place a room
	width += 6;
	height += 6;

	yPos -= 3;
	xPos -= 3;
	for (int y = yPos; y < yPos+height; y++) {
		for (int x = xPos; x < xPos+width; x++) {
			if (map.tileAt(x, y) != TILE_NOTHING) {
				return false;
			}
		}
	}
	return true;
}
void LevelGenerator::generateRoom(Map& map, int xPos, int yPos, int width, int height) {//place room
	width += 2;
	height += 2;

	for (int y = yPos - 1; y < yPos + height + 1; y++) {//makes ground around the rooms
		for (int x = xPos - 1; x < xPos + width + 1; x++) {
			//map.setTileAt(sf::Vector2i(x, y), TILE_GROUND);
		}
	}

	for (int y = yPos; y < yPos + height; y++) {
		for (int x = xPos; x < xPos + width; x++) {
			map.setTileAt(sf::Vector2i(x, y), TILE_INDOOR_GROUND);
			if (x == xPos|| x == xPos + width - 1) {
				map.setTileAt(sf::Vector2i(x, y), TILE_WALL);
			}
			if (y == yPos|| y == yPos + height - 1) {
				map.setTileAt(sf::Vector2i(x, y), TILE_WALL);
			}
		}
	}
	/*int doors = 1 + rand() % 2;
	for (int i = 0; i < doors; i++) {
		int doorX = xPos + rand() % width;
		int doorY = yPos + rand() % height;
		if (map.tileAt(doorX, doorY) == TILE_WALL) {
			map.setTileAt(doorX, doorY, TILE_DOOR);
		}
		else {
			i--;
		}
	}*/
	
}

void LevelGenerator::setLevel(int level) {
	this->level = level;
}