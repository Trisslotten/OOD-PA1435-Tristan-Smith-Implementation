#include "server.h"

#include <iostream>
#include <string>

void Server::update()
{

	std::shared_ptr< std::vector<sf::Packet> > packets = networking.receive();

	if (!packets->empty())
	{
		sf::Packet p = packets->at(0);
		std::string str;
		p >> str;
		std::cout << str << "\n";
	}
	


}
