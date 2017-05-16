#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <math.h>

class World;

class MapGenerator
{

public:

	virtual void setSeed(const std::string& seed) = 0;
	virtual void generateMap(World& world) = 0;

};


class TestGenerator : public MapGenerator
{
	std::string seed;
public:
	virtual void setSeed(const std::string& seed);
	virtual void generateMap(World& world);
};

class LevelGenerator : public MapGenerator {
private:
	int level = 1;
	std::string seed;
	
	std::string weaponsTitle[11] = { "Short Sword", "Club", "Halberd", "Scimitar", "Longsword", "Dagger", "Spear", "Flail", "Warhammer", "Axe", "Battle Axe" };
	std::string weaponsDesc[11] = { "A short sword made of steel, about the lenght of your forearm", "A wooden club, there are several splinters sticking out of it", "A halberd, the top of this long weapon is adorned by a large axe blade and a spear tip", "A scimitar, a curved steel blade", "A longsword made of steel, it is about a meter long", "A small dagger, usefull for cutting cheese", "A long wooden spear with a shart steel tip", "A flail, a large and spiked metal ball dangles from the end of a chain connected to the handle", "A warhammer, it is very heavy", "An axe, just like the one you might use to cut down trees", "A battle axe, its long handle ends with a two sided axe head" };
	const int weapons = 11;
	//tmp
	std::string mobTypes[12] = {"Rat","Dingo","Kobold","Hobo","Goblin","Orc","Ogre","Basilisk","Minotaur","Giant","Dragon","Hans the pelvis crusher"};
	std::string mobDesc[12] = {"A larger than usual rat","A wild dog","A small lizard-like creature","Small, green, annoying","A green humanoid, when it is not pillaging villages it works out at the local gym","It is very large and very angry", "A large crocodile-looking lizard, beware it gaze! No wait, that feature is not implemented", "50% human, 50% cow, 100% will kick your ass", "A giant humanoid, you question how he got this far down into the dungon","A large(r) lizard, with wings, and fangs","The crusher of pelvises worldwide. Prepare to enter the ring of pain, brother!"};
	char mobChar[12] = {'R','d','K','h','G','o','O','B','M','G','D','H'};
	const int mobs = 12;
public:
	virtual void setSeed(const std::string& seed);
	virtual void generateMap(World& world);
	void generateRoom(World& world, int xPos, int yPos, int width, int height);
	void setLevel(int level);
	bool checkRoomSpot(World& world, int xPos, int yPos, int width, int height);
};