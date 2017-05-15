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
		}
	}

}
void LevelGenerator::setSeed(const std::string & seed)
{
	this->seed = seed;
	srand(0);
}
void LevelGenerator::generateMap(Map & map) {
	int rooms = (rand() % 2)+2;
	int xPos = 4;
	int yPos = 5;
	int height = 10;
	int width = 8;

	std::cout << checkRoomSpot(map, xPos, yPos, width, height) << std::endl;
	generateRoom(map, xPos, yPos, width, height);
	std::cout << checkRoomSpot(map, xPos, yPos, width, height) << std::endl;
	std::cout << checkRoomSpot(map, xPos-1, yPos-1, width, height) << std::endl;
	std::cout << checkRoomSpot(map, xPos+1, yPos+1, width, height) << std::endl;
	std::cout << checkRoomSpot(map, xPos-1, yPos-1, width+2, height+2) << std::endl;
	std::cout << checkRoomSpot(map, xPos+1, yPos+1, width-2, height-2) << std::endl;
	for (int y = 0; y < map.getHeight(); y++) {
		for (int x = 0; x < map.getWidth(); x++) {
			if (map.tileAt(sf::Vector2i(x, y)) == TILE_NOTHING) {
				map.setTileAt(sf::Vector2i(x, y), TILE_GROUND);
			}
		}
	}
}
bool LevelGenerator::checkRoomSpot(Map& map, int xPos, int yPos, int width, int height) {//check if you can place a room
	for (int y = yPos; y < height; y++) {
		for (int x = xPos; x < width; x++) {
			if (map.tileAt(sf::Vector2i(x, y)) != TILE_NOTHING) {
				return false;
			}
		}
	}
	return true;
}
void LevelGenerator::generateRoom(Map& map, int xPos, int yPos, int width, int height) {//place room
	width += 2;
	height += 2;
	for (int y = yPos; y < yPos + height; y++) {
		for (int x = xPos; x < xPos + width; x++) {
			map.setTileAt(sf::Vector2i(x, y), TILE_GROUND);
			if (x == xPos || x == xPos + width-1) {
				map.setTileAt(sf::Vector2i(x, y), TILE_WALL);
			}
			if (y == yPos || y == yPos + height-1) {
				map.setTileAt(sf::Vector2i(x, y), TILE_WALL);
			}
		}
	}
}
void LevelGenerator::setLevel(int level) {
	this->level = level;
}