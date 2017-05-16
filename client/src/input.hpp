#pragma once

#include <SFML/Window.hpp>

namespace key
{
	void update();
	bool pressed(sf::Keyboard::Key key);
	bool released(sf::Keyboard::Key key);
	bool down(sf::Keyboard::Key key);
}
