#include "networking.hpp"

#include <SFML/Network.hpp>
#include <memory>

Networking::Networking(unsigned short port)
{
	socket.bind(port);
	socket.setBlocking(true);
}

std::shared_ptr< std::vector<sf::Packet> > Networking::receive()
{
	std::shared_ptr< std::vector<sf::Packet> > packets = std::make_shared<std::vector<sf::Packet>>();

	sf::Clock clock;
	clock.restart();
	// TODO: set time as parameter
	while (clock.getElapsedTime() < sf::seconds(1.0 / 15))
	{
		sf::Packet packet;
		sf::IpAddress address;
		unsigned short port;
		socket.receive(packet, address, port);

		// maybe add ip and port
		packets->push_back(packet);
	}


	return packets;
}

void Networking::sendSnapshot(World & world)
{}
