#include "networking.hpp"

#include <iostream>

#include <SFML/Network.hpp>
#include <memory>
#include "definitions.hpp"

Networking::Networking(Port port)
{
	socket.bind(port);
	socket.setBlocking(true);
}

std::shared_ptr< std::vector<Packet> > Networking::receive()
{
	std::shared_ptr< std::vector<Packet> > packets = std::make_shared<std::vector<Packet>>();

	sf::Clock clock;
	clock.restart();
	// TODO: set time as parameter
	while (clock.getElapsedTime() < sf::seconds(1.0 / 15))
	{
		Packet packet;
		socket.receive(packet.packet, packet.address, packet.port);

		// maybe add ip and port
		packets->push_back(packet);
	}


	return packets;
}

void Networking::sendSnapshot(World & world)
{

}

void Networking::addClient(ID mob_id, sf::IpAddress ip, Port port)
{
	ID new_id = client_id_counter;
	client_id_counter++;

	Client client;
	client.id = new_id;
	client.address = ip;
	client.mob_id = mob_id;
	client.port = port;

	clients[new_id] = client;

	std::cout << "Client added\n\tid: " << client.id << "\n\tip: " << client.address << "\n\tport: " << client.port << "\n";
}
