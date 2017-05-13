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
	ID new_id = mob_ids.newID();

	Player new_player(new_id);

	players[new_id] = new_player;
	return new_id;
}

void World::removePlayer(ID mob_id)
{
	players.erase(mob_id);
}

// when client joins
// append map and mob data to packet
void World::serializeWorldState(sf::Packet& to_append)
{	// maybe split into different functions for each list (players, npcs, tiles etc)
	to_append << players.size();
	for (auto&& map_elem : players)
	{
		Mob p = map_elem.second;
		sf::Vector2i pos = p.getPos();
		//std::cout << "Appending id: " << map_elem.second.getID() << "\n";
		to_append << p.getID() << pos.x << pos.y;
	}
}

// each frame
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
