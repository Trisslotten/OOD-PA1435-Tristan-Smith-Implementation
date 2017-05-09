#pragma once

#include <SFML/Network.hpp>
#include "definitions.hpp"


struct Client
{
	ID id;
	ID mob_id;
	sf::IpAddress address;
	Port port;
};