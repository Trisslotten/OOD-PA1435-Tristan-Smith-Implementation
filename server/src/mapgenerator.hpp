#pragma once

#include <string>
#include <iostream>
#include <vector>

class Map;

class MapGenerator
{

public:

	virtual void setSeed(const std::string& seed) = 0;
	virtual void generateMap(Map& map) = 0;

};


class TestGenerator : public MapGenerator
{
	std::string seed;
public:
	virtual void setSeed(const std::string& seed);
	virtual void generateMap(Map& map);
};

class LevelGenerator : public MapGenerator {
private:
	int level = 0;
	std::string seed;
public:
	virtual void setSeed(const std::string& seed);
	virtual void generateMap(Map& map);
	void generateRoom(Map& map, int xPos, int yPos, int width, int height);
	void setLevel(int level);
	bool checkRoomSpot(Map& map, int xPos, int yPos, int width, int height);
};