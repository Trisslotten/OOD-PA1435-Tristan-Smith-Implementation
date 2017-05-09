#pragma once

#include <SFML/Network.hpp>

#include "../../shared/definitions.hpp"

struct Packet
{
	sf::Packet packet;
	sf::IpAddress address;
	Port port;
};