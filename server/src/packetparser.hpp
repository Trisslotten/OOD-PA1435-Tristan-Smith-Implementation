#pragma once

#include <SFML/Network.hpp>
#include <memory>
#include <vector>

#include "networking.hpp"
#include "world.hpp"
#include "packet.hpp"

class PacketParser
{


	void joinServer(Packet& packet, Networking& networking, World& world);
public:

	void parse(std::shared_ptr<std::vector<Packet>> packets, Networking& networking, World& world);

};