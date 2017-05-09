#include "packetparser.hpp"

#include <iostream>

#include "../../shared/definitions.hpp"

#include "engine.hpp"
#include "world.hpp"

void PacketParser::parse(std::shared_ptr<std::vector<sf::Packet>> packets, Engine & engine, World & world)
{
	for (auto&& packet : *packets)
	{
		unsigned int action;
		packet >> action;


		std::string msg;
		switch (action)
		{
		case TC_CONFIRM_JOIN:
			

			break;
		case TC_DEBUG_SEND_STRING:
			packet >> msg;
			std::cout << msg << "\n";
			break;
		case TC_SERVER_SHUTDOWN:


			break;
		case TC_DEBUG_SET_POS:
			debugMove(packet, engine, world);
			break;
		default:
			// error message?
			break;
		}
	}
}


void PacketParser::debugMove(sf::Packet & packet, Engine & engine, World & world)
{
	packet >> engine.test_pos.x >> engine.test_pos.y;


	std::cout << "RECEIVE: test move" << engine.test_pos.x << " " << engine.test_pos.y << "\n";
}