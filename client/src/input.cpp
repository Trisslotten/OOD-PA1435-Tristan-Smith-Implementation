#include "input.hpp"

namespace
{
	bool keys[sf::Keyboard::KeyCount];
	bool prev_keys[sf::Keyboard::KeyCount];
}

void key::update()
{
	for (int i = 0; i < sf::Keyboard::KeyCount; i++)
	{
		prev_keys[i] = keys[i];
		keys[i] = sf::Keyboard::isKeyPressed((sf::Keyboard::Key)i);
	}
}

bool key::pressed(sf::Keyboard::Key key)
{
	return keys[key] && !prev_keys[key];
}

bool key::released(sf::Keyboard::Key key)
{
	return keys[key] && !prev_keys[key];
}

bool key::down(sf::Keyboard::Key key)
{
	return keys[key] && prev_keys[key];
}
