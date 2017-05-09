#pragma once

#include <SFML/Network.hpp>

#include "definitions.hpp"

struct Packet
{
	sf::Packet packet;
	sf::IpAddress address;
	Port port;
};