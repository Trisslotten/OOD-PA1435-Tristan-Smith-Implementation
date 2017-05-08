#pragma once

#include <SFML/Network.hpp>

struct Client
{
	unsigned int clientID;
	unsigned int mobID;
	sf::IpAddress address;
	unsigned short port;
};