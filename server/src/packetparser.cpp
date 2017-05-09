#include "packetparser.hpp"

#include <SFML/Network.hpp>
#include "../../shared/definitions.hpp"
#include "packet.hpp"

#include <iostream>


void PacketParser::parse(std::shared_ptr<std::vector<Packet>> packets, Networking & networking, World & world)
{
	for (auto&& p : *packets)
	{
		unsigned int action;
		p.packet >> action;
		switch (action)
		{
		case TS_JOIN_SERVER:
			joinServer(p, networking, world);
			break;
		case TS_DISCONNECT:

			break;
		case TS_DEBUG_MOVE:
			debugMove(p, networking, world);
			break;
		default:
			// error message?
			break;
		}
	}
}


void PacketParser::joinServer(Packet& packet, Networking & networking, World & world)
{
	//ID mob_id = world.createPlayer();

	networking.addClient(0, packet.address, packet.port);
}


void PacketParser::debugMove(Packet & packet, Networking & networking, World & world)
{
	sf::Vector2i vel;
	packet.packet >> vel.x >> vel.y;
	std::cout << "RECEIVE: test move " << vel.x << " " << vel.y << "\n";

	world.test_pos += vel;
}