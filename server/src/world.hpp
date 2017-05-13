#pragma once

#include "../../shared/definitions.hpp"

#include <SFML/Network.hpp>
#include "mob.hpp"
#include "player.hpp"
#include <unordered_map>

class World
{

	std::unordered_map<ID, Mob> npcs;
	ID npcs_id_counter = 0;

	// maybe change to own class for inventory etc
	std::unordered_map<ID, Player> players;
	ID players_id_counter = 0;

	std::unordered_map<ID, Item> items_on_ground;
	ID items_id_counter = 0;
	
public:

	void movePlayer(ID mob_id, sf::Vector2i vel);

	ID createPlayer();
	void removePlayer(ID mob_id);

	void placeItemOnGround(Item item);

	// maybe split into different functions for each list (players, npcs, tiles etc)
	void serializeWorldState(sf::Packet& to_append);

	void serializeSnapshot(sf::Packet& to_append);

	Player* getPlayerById(ID id);
};