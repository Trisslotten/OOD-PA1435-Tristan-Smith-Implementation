#include "server.h"

#include <iostream>
#include <string>

void Server::update()
{

	std::shared_ptr< std::vector<Packet> > packets = networking.receive();

	if (!packets->empty())
	{
		Packet p = packets->at(0);
		std::string str;
		p.packet >> str;
		std::cout << str << "\n";
	}

	packet_parser.parse(packets, networking, world);


}
