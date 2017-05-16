#pragma once

#include <SFML/Network.hpp>
#include <memory>
#include <vector>

#include "networking.hpp"
#include "world.hpp"
#include "packet.hpp"

class PacketParser
{

	//TODO: change parameters to Server and add getters for networking and world
	void joinServer(Packet& packet, Networking& networking, World& world);
	void disconnectClient(Packet& packet, Networking& networking, World& world);
	void dropItem(Packet& packet, Networking& networking, World& world);

	void parseMovePlayer(Packet& packet, Networking& networking, World& world);
	void pickupItem(Packet& packet, Networking& networking, World& world);
	void requestInventory(Packet& packet, Networking& networking, World& world);
	void requestDescriptions(Packet& packet, Networking& networking, World& world);
	void equipItem(Packet& packet, Networking& networking, World& world);
	void requestEquipped(Packet& packet, Networking& networking, World& world);
public:

	void parse(std::shared_ptr<std::vector<Packet>> packets, Networking& networking, World& world);

};