#include "mapgenerator.hpp"
#include "world.hpp"


void TestGenerator::setSeed(const std::string & seed)
{
	this->seed = seed;
}

void TestGenerator::generateMap(World& world)
{
	for (int y = 0; y < world.getMap().getHeight(); y++)
	{
		for (int x = 0; x < world.getMap().getWidth(); x++)
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
			world.getMap().setTileAt(x, y, (Tile)asd);
		}
	}

}
void LevelGenerator::setSeed(const std::string & seed)
{
	this->seed = seed;
}
void LevelGenerator::generateMap(World & world) {
	srand(time(NULL));

	int rooms = (rand() % 3)+2;
	std::vector<sf::Vector2i> points;
	int attempts=0;
	for (int i = 0; i < rooms && attempts < 100; i++) {

		int height = (rand() % 15) + 5;
		int width = (rand() % 15) + 5;

		int xPos = 1 + rand()%(world.getMap().getWidth() - width-3);
		int yPos = 1 + rand() % (world.getMap().getHeight() - height-3);

		if (checkRoomSpot(world, xPos, yPos, width, height)) {
			generateRoom(world, xPos, yPos, width, height);
			points.push_back(sf::Vector2i(xPos + width/2, yPos + height/2));
		}
		else {
			i--;
			attempts++;
		}
	}

	//add up/down stairs to access new levels of the dungeon
	while (true) {//shit code
		int stairsX = rand() % world.getMap().getWidth();
		int stairsY = rand() % world.getMap().getHeight();
		if (world.getMap().tileAt(stairsX, stairsY) == TILE_INDOOR_GROUND) {
			world.getMap().setTileAt(stairsX, stairsY, TILE_STAIRS_DOWN);
			break;
		}
	}
	while (true) {
		int stairsX = rand() % world.getMap().getWidth();
		int stairsY = rand() % world.getMap().getHeight();
		if (world.getMap().tileAt(stairsX, stairsY) == TILE_INDOOR_GROUND) {
			world.getMap().setTileAt(stairsX, stairsY, TILE_STAIRS_UP);
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
				if (world.getMap().tileAt(sf::Vector2i(x2, y2)) != TILE_WALL && world.getMap().tileAt(sf::Vector2i(x2, y2)) != TILE_DOOR) {
					insideWall = false;
				}
				if (insideWall) {
					x2 = oldX2;
					y2 = oldY2;
				}
				if (world.getMap().tileAt(sf::Vector2i(x2, y2)) == TILE_NOTHING) {
					world.getMap().setTileAt(x2, y2, TILE_GROUND);
				}
				if (world.getMap().tileAt(sf::Vector2i(x2, y2)) == TILE_WALL && !insideWall) {
					world.getMap().setTileAt(x2, y2, TILE_DOOR);
					insideWall = true;
				}
				attempts++;
			}
		}
		points.pop_back();
	}

	//place loot in level
	int lootNum = 3 + rand() % 7;
	for (int i = 0; i < lootNum; i++) {
		int x = rand() % world.getMap().getWidth();
		int y = rand() % world.getMap().getHeight();
		if (world.getMap().tileAt(sf::Vector2i(x, y)) == TILE_INDOOR_GROUND) {
			int wep = rand() % weapons;
			ID newid = world.item_ids.newID();

			int attackModifier = 0;

			sf::Color quality = QUALITY_COMMON;
			int roll = (rand() % 1000) + 1;
			if (roll<200) {
				quality = QUALITY_UNCOMMON;
				attackModifier++;
				if (roll<100) {
					quality = QUALITY_RARE;
					attackModifier++;
					if (roll<50) {
						quality = QUALITY_EPIC;
						attackModifier+=2;
						if (roll == 1) {
							quality = QUALITY_LEGENDARY;
							attackModifier+=4;
						}
					}
				}
			}

			world.items_on_ground[newid] = Item(newid, weaponsTitle[wep], weaponsDesc[wep], 'I', sf::Vector2i(x, y), quality, attackModifier + level + rand() % 5);
		}
		else {
			i--;
		}
	}

	int mobNum = 3 + rand() % 7;
	for (int i = 0; i < mobNum; i++) {
		int x = rand() % world.getMap().getWidth();
		int y = rand() % world.getMap().getHeight();
		if (world.getMap().tileAt(sf::Vector2i(x, y)) == TILE_GROUND || world.getMap().tileAt(sf::Vector2i(x, y)) == TILE_INDOOR_GROUND) {
			
		}
		else {
			i--;
		}
	}

	std::cout << "map generation done!" << std::endl;
}
bool LevelGenerator::checkRoomSpot(World& world, int xPos, int yPos, int width, int height) {//check if you can place a room
	width += 6;
	height += 6;

	yPos -= 3;
	xPos -= 3;
	for (int y = yPos; y < yPos+height; y++) {
		for (int x = xPos; x < xPos+width; x++) {
			if (world.getMap().tileAt(x, y) != TILE_NOTHING) {
				return false;
			}
		}
	}
	return true;
}
void LevelGenerator::generateRoom(World& world, int xPos, int yPos, int width, int height) {//place room
	width += 2;
	height += 2;

	for (int y = yPos - 1; y < yPos + height + 1; y++) {//makes ground around the rooms
		for (int x = xPos - 1; x < xPos + width + 1; x++) {
			//map.setTileAt(sf::Vector2i(x, y), TILE_GROUND);
		}
	}

	for (int y = yPos; y < yPos + height; y++) {
		for (int x = xPos; x < xPos + width; x++) {
			world.getMap().setTileAt(sf::Vector2i(x, y), TILE_INDOOR_GROUND);
			if (x == xPos|| x == xPos + width - 1) {
				world.getMap().setTileAt(sf::Vector2i(x, y), TILE_WALL);
			}
			if (y == yPos|| y == yPos + height - 1) {
				world.getMap().setTileAt(sf::Vector2i(x, y), TILE_WALL);
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