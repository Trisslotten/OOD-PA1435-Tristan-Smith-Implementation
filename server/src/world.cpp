#include "world.hpp"

#include <iostream>

void World::movePlayer(ID mob_id, sf::Vector2i vel)
{
	if (players.count(mob_id) > 0)
	{
		players[mob_id].pos += vel;
	}
}

ID World::createPlayer()
{
	ID new_id = players_id_counter;
	players_id_counter++;

	Player new_player(new_id);

	/*
	Player mob;
	mob.id = new_id;
	mob.pos = sf::Vector2i();*/
	players[new_id] = new_player;
	return new_id;
}

void World::removePlayer(ID mob_id)
{
	players.erase(mob_id);
}

// append map and mob data to packet
void World::serializeWorldState(sf::Packet& to_append)
{	// maybe split into different functions for each list (players, npcs, tiles etc)
	to_append << players.size();
	for (auto&& map_elem : players)
	{
		Mob p = map_elem.second;
		std::cout << "Appending id: " << map_elem.second.id << "\n";
		to_append << p.id << p.pos.x << p.pos.y;
	}
}

void World::serializeSnapshot(sf::Packet & to_append)
{
	to_append << players.size();
	for (auto&& map_elem : players)
	{
		Mob p = map_elem.second;
		to_append << p.id << p.pos.x << p.pos.y;
	}
}

Player* World::getPlayerById(ID id)
{
	if (players.count(id) > 0)
	{
		return &players[id];
	}
}

void World::placeItemOnGround(Item item)
{
	this->items_on_ground[item.getItemId()] = item;
}
