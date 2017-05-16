#pragma once

#include "mob.hpp"
#include <unordered_map>
#include "item.hpp"

class Player : public Mob
{
private:
	std::unordered_map<ID, Item> inventory;
public:
	Player() {}
	void removeItem(ID item_id);
	void addItem(Item item);
	Item getItemById(ID id);

	inline std::unordered_map<ID, Item> getInventory() { return inventory; }
	Player(ID id);
};