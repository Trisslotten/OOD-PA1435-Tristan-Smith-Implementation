#include "player.hpp"

Player::Player(ID id) : Mob(id)
{
	this->symbol = '@';
}

void Player::removeItem(ID id)
{
	inventory.erase(id);
}

Item Player::getItemById(ID id)
{
	if (this->inventory.count(id) > 0)
	{
		return inventory[id];
	}
}