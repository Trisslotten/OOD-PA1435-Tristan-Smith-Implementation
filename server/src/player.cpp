#include "player.hpp"

Player::Player(ID id) : Mob(id)
{
	this->symbol = '@';
}

void Player::removeItem(ID id)
{
	inventory.erase(id);
	if (id == this->equipID)
	{
		equipID = ID_NOT_FOUND;
	}
}

void Player::addItem(Item item)
{
	inventory[item.getItemId()] = item;
}

Item Player::getItemById(ID id)
{
	if (this->inventory.count(id) > 0)
		return inventory[id];
	else
		return Item();
}