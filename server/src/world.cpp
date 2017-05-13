#include "world.hpp"

#include <iostream>

void World::movePlayer(ID mob_id, sf::Vector2i vel)
{
	if (players.count(mob_id) > 0)
	{
		sf::Vector2i pos = players[mob_id].getPos();
		pos += vel;
		players[mob_id].setPos(pos);
	}
}

ID World::createPlayer()
{
	ID new_id = players_id_counter;
	players_id_counter++;


	Mob mob;
	mob.setID(new_id);
	mob.setPos(sf::Vector2i());
	players[new_id] = mob;
	return new_id;
}

void World::removePlayer(ID mob_id)
{
	players.erase(mob_id);
}

// for when client joins
// append map and mob data to packet
void World::serializeWorldState(sf::Packet& to_append)
{	// maybe split into different functions for each list (players, npcs, tiles etc)
	to_append << players.size();
	for (auto&& map_elem : players)
	{
		Mob p = map_elem.second;
		sf::Vector2i pos = p.getPos();
		std::cout << "Appending id: " << map_elem.second.getID() << "\n";
		to_append << p.getID() << pos.x << pos.y;
	}
}

// for each frame
void World::serializeSnapshot(sf::Packet & to_append)
{
	to_append << players.size();
	for (auto&& map_elem : players)
	{
		Mob p = map_elem.second;
		sf::Vector2i pos = p.getPos();
		to_append << p.getID() << pos.x << pos.y;
	}
}
