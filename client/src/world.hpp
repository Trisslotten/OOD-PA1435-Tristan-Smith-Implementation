#pragma once

#include <unordered_map>

#include "../../shared/definitions.hpp"
#include "mob.hpp"

#include "renderer.hpp"
#include "map.hpp"

class World
{

	Map map;

	// players and npcs
	std::unordered_map<ID, Mob> mobs;

	ID player_id;



public:

	void render(Renderer& renderer);

	void setPlayerID(ID id);

	inline Map& getMap()
	{
		return map;
	}

	void addMob(ID mob_id, sf::Vector2i pos);
	void removeMob(ID mob_id);
	void moveMob(ID mob_id, sf::Vector2i vel);
	void setMobPos(ID mob_id, sf::Vector2i pos);
};