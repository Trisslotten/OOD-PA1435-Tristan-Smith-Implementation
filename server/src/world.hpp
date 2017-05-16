#pragma once

#include "../../shared/definitions.hpp"

#include <SFML/Network.hpp>
#include "mob.hpp"
#include "player.hpp"
#include "idcreator.hpp"
#include "map.hpp"
#include "mapgenerator.hpp"
#include <unordered_map>

class World
{
	Map map{ 50,50 };

	std::unordered_map<ID, Player> players;
	// one for both since one list on client
	
public:

	std::unordered_map<ID, Item> items_on_ground;
	IDCreator item_ids;

	std::unordered_map<ID, Mob> npcs;
	IDCreator mob_ids;

	void init();

	void update();

	Map& getMap()
	{
		return map;
	}

	std::string getDescriptions(sf::Vector2i pos);

	void movePlayer(ID mob_id, sf::Vector2i vel);

	ID createPlayer();
	void removePlayer(ID mob_id);

	void placeItemOnGround(Item item);

	// maybe split into different functions for each list (players, npcs, tiles etc)
	void serializeWorldState(sf::Packet& to_append);

	void serializeSnapshot(sf::Packet& to_append);

	Player* getPlayerById(ID id);

	inline std::unordered_map<ID, Item> getItems() { return items_on_ground; }

	void pickupItemFromGround(Player* player, ID item_id);

	inline Item getItemById(ID id) { return items_on_ground[id]; }

	ID getItemAtPos(sf::Vector2i pos);


	IDCreator getItem_ids();
	std::unordered_map<ID, Item> getItems_on_ground();

	Mob* getMobAt(sf::Vector2i pos);

	void removeMob(ID id) { this->npcs.erase(id); }

};