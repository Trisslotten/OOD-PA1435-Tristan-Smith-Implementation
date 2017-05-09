#include "server.h"

#include <iostream>
#include <string>

void Server::update()
{
	
	networking.sendSnapshot(world);

}

void Server::receive(sf::Time receive_time)
{
	std::shared_ptr< std::vector<Packet> > packets = networking.receive(receive_time);
	if (!packets->empty())
	{
		packet_parser.parse(packets, networking, world);
	}
}
