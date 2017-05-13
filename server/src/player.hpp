#pragma once

#include "mob.hpp"
#include <unordered_map>
#include "item.hpp"

class Player : public Mob
{
private:
	std::unordered_map<ID, Item> inventory;
public:
	void removeItem(ID item_id);
	void addItem(Item item);
	Item getItemById(ID id);
	Player(ID id);
};