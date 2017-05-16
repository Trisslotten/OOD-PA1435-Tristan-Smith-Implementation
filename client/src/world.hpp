#pragma once

#include <unordered_map>

#include "../../shared/definitions.hpp"
#include "mob.hpp"

#include "renderer.hpp"
#include "map.hpp"
#include "item.hpp"

class World
{

	Map map;

	// players and npcs
	std::unordered_map<ID, Mob> mobs;
	std::unordered_map<ID, Item> items;
	ID player_id;

	std::vector<Item> latest_inventory;
	std::string latest_descriptions;
	ID latest_equipped = ID_NOT_FOUND;
public:

	void render(Renderer& renderer);

	void setPlayerID(ID id);

	inline Map& getMap()
	{
		return map;
	}
	
	sf::Vector2i getPlayerPos();
	void addMob(ID mob_id, sf::Vector2i pos);
	void addMob(ID mob_id, sf::Vector2i pos, char symbol);
	void removeMob(ID mob_id);
	void moveMob(ID mob_id, sf::Vector2i vel);
	void setMobPos(ID mob_id, sf::Vector2i pos);
	void addItem(Item item);
	void removeItem(ID id);


	void setLatestDescriptions(const std::string& descs) { latest_descriptions = descs; }
	std::string getLatestDescriptions() { return latest_descriptions; }
	void setLatestInventory(std::vector<Item> inv) { latest_inventory = inv; }
	std::vector<Item> getLatestInventory() { return latest_inventory; }
	void setLatestEquipped(ID id) { this->latest_equipped = id; }
	ID getLatestEquipped() { return latest_equipped; }
	Item getInventoryItemByID(ID id);
};