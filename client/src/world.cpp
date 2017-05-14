#include "world.hpp"
#include <iostream>
#include "renderer.hpp"

void World::render(Renderer & renderer)
{
	sf::Vector2i offset;
	if(mobs.count(player_id) > 0)
		offset = mobs[player_id].getPos() - renderer.getScreenSizeTiles()/2;

	map.render(renderer, offset);

	for (auto&& map_elem : mobs)
	{
		Mob mob = map_elem.second;
		renderer.drawChar(mob.getPos() - offset, mob.getSymbol(), mob.getColor());
	}
}
void World::setPlayerID(ID id)
{
	player_id = id;
}

void World::addMob(ID mob_id, sf::Vector2i pos)
{
	Mob mob;
	mob.setID(mob_id);
	mob.setPos(pos);
	mob.setSymbol('@');
	mob.setColor(sf::Color::White);
	mobs[mob_id] = mob;
}

void World::removeMob(ID mob_id)
{
	if (mobs.count(mob_id) > 0)
	{
		mobs.erase(mob_id);
	}
}

void World::moveMob(ID mob_id, sf::Vector2i vel)
{	
	if (mobs.count(mob_id) > 0)
	{
		mobs[mob_id].move(vel);
	}
}

void World::setMobPos(ID mob_id, sf::Vector2i pos)
{
	if (mobs.count(mob_id) > 0)
	{
		mobs[mob_id].setPos(pos);
	}
}
