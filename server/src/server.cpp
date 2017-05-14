#include "server.hpp"

#include <iostream>
#include <string>

void Server::init()
{
	world.init();
}

void Server::update()
{
	networking.sendSnapshot(world);
}

void Server::receive(sf::Time receive_time)
{
	std::shared_ptr< std::vector<Packet> > packets = networking.receive(receive_time);
	if (!packets->empty())
	{
		std::cout << "Num packets: " << packets->size() << "\n";
		packet_parser.parse(packets, networking, world);
	}
}
