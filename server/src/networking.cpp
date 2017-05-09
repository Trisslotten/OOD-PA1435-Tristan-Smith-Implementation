#include "networking.hpp"

#include <iostream>

#include <SFML/Network.hpp>
#include <memory>
#include "../../shared/definitions.hpp"

void Networking::send(sf::Packet packet, Client client)
{
	socket.send(packet, client.address, client.port);
}

Networking::Networking(Port port)
{
	socket.bind(port);
	socket.setBlocking(true);
}

std::shared_ptr< std::vector<Packet> > Networking::receive(sf::Time receive_time)
{
	auto packets = std::make_shared<std::vector<Packet>>();

	sf::Clock clock;
	clock.restart();
	while (clock.getElapsedTime() < receive_time)
	{
		Packet packet;
		sf::Socket::Status status = socket.receive(packet.packet, packet.address, packet.port);
		if (status == sf::Socket::Done)
		{
			unsigned int program_id;
			packet.packet >> program_id;
			if (program_id == PROGRAM_ID)
				packets->push_back(packet);
		}
	}
	return packets;
}

void Networking::sendSnapshot(World & world)
{
	sf::Packet packet;
	packet << PROGRAM_ID << TC_DEBUG_SET_POS;
	packet << world.test_pos.x << world.test_pos.y;

	std::cout << "SENDING: world snapshot\n";
	for (auto&& map_elem : clients)
	{
		Client client = map_elem.second;
		send(packet, client);
	}
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


