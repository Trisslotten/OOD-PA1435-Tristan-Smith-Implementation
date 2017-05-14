#pragma once

#include <string>

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