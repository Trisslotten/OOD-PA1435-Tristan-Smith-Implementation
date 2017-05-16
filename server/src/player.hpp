#pragma once

#include "mob.hpp"
#include <unordered_map>
#include "item.hpp"

class Player : public Mob
{
private:
	std::unordered_map<ID, Item> inventory;
	ID equipID = ID_NOT_FOUND;
public:
	Player() {}
	void removeItem(ID item_id);
	void addItem(Item item);
	Item getItemById(ID id);

	inline std::unordered_map<ID, Item> getInventory() { return inventory; }
	inline ID getEquipped() { return equipID; }
	inline void equip(ID item_id) { this->equipID = item_id; }
	Player(ID id);
};