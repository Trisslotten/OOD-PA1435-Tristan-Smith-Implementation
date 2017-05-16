#include "world.hpp"

#include <iostream>
#include <memory>

void World::init()
{
	std::shared_ptr<MapGenerator> generator = std::make_shared<LevelGenerator>();
	generator->generateMap(*this);

	
	// debug
	for (int i = 0; i < map.getHeight(); i++)
	{
		for (int j = 0; j < map.getWidth(); j++)
		{
			sf::Int8 t = map.tileAt(i, j);
			if (getItemAtPos(sf::Vector2i(i, j)) != ID_NOT_FOUND) {
				std::cout << 'I';
			}
			else {
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
				case TILE_STAIRS_DOWN:
					std::cout << 'v';
					break;
				case TILE_STAIRS_UP:
					std::cout << '^';
					break;
				case TILE_DOOR:
					std::cout << '|';
					break;
				case TILE_INDOOR_GROUND:
					std::cout << ',';
					break;
				}
			}
		}
		std::cout << '\n';
	}


	std::cout << "len: " << items_on_ground.size() << std::endl;
	for (int i = 0; i < items_on_ground.size(); i++) {
		std::cout << items_on_ground[i].getName() << " " << (int)items_on_ground[i].getColor().r << " " << (int)items_on_ground[i].getColor().g << " " << (int)items_on_ground[i].getColor().b << std::endl;
	}
	//test items
	ID newid = this->item_ids.newID();
	this->items_on_ground[newid] = Item(newid, "The Crazy Thing", "The craziest thing", 'T', sf::Vector2i(7, 7), QUALITY_EPIC,10);
	
	for (int i = 0; i < 80; i++)
	{
		newid = this->item_ids.newID();
		this->items_on_ground[newid] = Item(newid, "Frostmourne " + std::to_string(i) , "oh shieet", 'F', sf::Vector2i(5, 8), QUALITY_LEGENDARY,20);
	}
	for (int x = 0; x < 5; x++)
	{
		for (int y = 0; y < 5; y++)
		{
			newid = this->mob_ids.newID();
			this->npcs[newid] = Mob(newid, "Test monster " + std::to_string(x + y), "The craziest boy", sf::Vector2i(-5+x, -5+y), 100, 100);
		}
	}
}

void World::update()
{
	for (auto&& map_elem : players)
	{
		map_elem.second.update();
	}
}

std::string World::getDescriptions(sf::Vector2i pos)
{
	std::string result;
	for (auto i : items_on_ground)
	{
		if (i.second.getPos() == pos)
		{
			result += i.second.getName() + "\n" + i.second.getDescription() + "\n";
		}
	}
	for (auto i : players)
	{
		if (i.second.getPos() == pos)
		{
			result += i.second.getName() + "\n" + i.second.getDescription() + "\n";
		}
	}
	for (auto i : npcs)
	{
		if (i.second.getPos() == pos)
		{
			result += i.second.getName() + "\n" + i.second.getDescription() + "\n";
		}
	}
	switch (map.tileAt(pos))
	{
	case TILE_WALL:
		result += "Wall\n";
		break;
	case TILE_DOOR:
		result += "Door\n";
		break;
	case TILE_GROUND:
		result += "Ground\n";
		break;
	case TILE_INDOOR_GROUND:
		result += "Floor\n";
		break;
	case TILE_STAIRS_DOWN:
		result += "Stairs down\n";
		break;
	case TILE_STAIRS_UP:
		result += "Stairs up\n";
		break;
	}
	return result;
}

void World::movePlayer(ID mob_id, sf::Vector2i vel)
{
	if (players.count(mob_id) > 0)
	{
		if (!getMap().isWallAt(players[mob_id].getPos() + vel))
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
	to_append << players.size()+npcs.size();
	for (auto&& map_elem : players)
	{
		Mob p = map_elem.second;
		sf::Vector2i pos = p.getPos();
		//std::cout << "Appending id: " << map_elem.second.getID() << "\n";
		to_append << p.getID() << pos.x << pos.y << p.getSymbol();
	}
	for (auto&& map_elem : npcs)
	{
		Mob p = map_elem.second;
		sf::Vector2i pos = p.getPos();
		//std::cout << "Appending id: " << map_elem.second.getID() << "\n";
		to_append << p.getID() << pos.x << pos.y << p.getSymbol();
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
		return &players[id];
	else
		return nullptr;
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

IDCreator World::getItem_ids() {
	return this->item_ids;
}

std::unordered_map<ID, Item> World::getItems_on_ground() {
	return this->items_on_ground;
}

Mob* World::getMobAt(sf::Vector2i pos)
{
	Mob* returnmob = nullptr;
	for (auto&& map_elem : this->npcs)
	{
		if (map_elem.second.getPos() == pos)
		{
			return &map_elem.second;
		}
	}
	return returnmob;
}

