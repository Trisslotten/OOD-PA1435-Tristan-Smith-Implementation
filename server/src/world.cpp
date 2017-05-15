#include "world.hpp"

#include <iostream>
#include <memory>

void World::init()
{
	std::shared_ptr<MapGenerator> generator = std::make_shared<TestGenerator>();
	generator->generateMap(map);

	/*
	// debug
	for (int i = 0; i < map.getHeight(); i++)
	{
		for (int j = 0; j < map.getWidth(); j++)
		{
			sf::Int8 t = map.tileAt(i, j);

			switch (t)
			{
			case TILE_NOTHING:
				std::cout << ' ';
				break;
			case TILE_WALL:
				std::cout << '#';
				break;
			case TILE_GROUND:
				std::cout << '.';
				break;
			}
		}
		std::cout << '\n';
	}
	*/
	//test items
	ID newid = this->item_ids.newID();
	this->items_on_ground[newid] = Item(newid, "The Crazy Thing", "The craziest thing", 'T', sf::Vector2i(7, 7), QUALITY_EPIC);
	
	for (int i = 0; i < 80; i++)
	{
		newid = this->item_ids.newID();
		this->items_on_ground[newid] = Item(newid, "Frostmourne " + std::to_string(i) , "oh shieet", 'F', sf::Vector2i(5, 8), QUALITY_LEGENDARY);
	}
}

void World::update()
{
	for (auto&& map_elem : players)
	{
		map_elem.second.update();
	}
}

void World::movePlayer(ID mob_id, sf::Vector2i vel)
{
	if (players.count(mob_id) > 0)
	{
		players[mob_id].setVel(vel);
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

ID World::getItemAtPos(sf::Vector2i pos)
{
	ID retid = ID_NOT_FOUND;
	//check if there is an item wher player is standing

	for (auto&& map_element : items_on_ground)
	{
		if (map_element.second.getPos() == pos)
		{
			retid = map_element.second.getItemId();
		}
	}
	return retid;
}

void World::pickupItemFromGround(Player* player, ID item_id)
{
	if (items_on_ground.count(item_id) > 0)
	{
		//place in player's inventory
		player->addItem(items_on_ground[item_id]);
		items_on_ground.erase(item_id);
	}
}