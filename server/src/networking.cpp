#include "networking.hpp"

#include <iostream>

#include <SFML/Network.hpp>
#include <memory>

#include "../../shared/definitions.hpp"
#include "world.hpp"

void Networking::send(sf::Packet packet, Client client)
{
	socket.send(packet, client.address, client.port);
}

sf::Socket::Status Networking::receiveTimeout(Packet& packet, sf::Time timeout)
{
	sf::SocketSelector selector;
	selector.add(socket);
	if (selector.wait(timeout))
		return socket.receive(packet.packet, packet.address, packet.port);
	else
		return sf::Socket::NotReady;
}

Networking::Networking(Port port)
{
	socket.bind(port);
	socket.setBlocking(false);
}

Networking::~Networking()
{
	sf::Packet packet;
	packet << PROGRAM_ID << TC_SERVER_SHUTDOWN;
	for (auto map_elem : clients)
	{
		send(packet, map_elem.second);
	}
}

std::shared_ptr< std::vector<Packet> > Networking::receive(sf::Time receive_time)
{
	sf::Clock clock;
	clock.restart();
	auto packets = std::make_shared<std::vector<Packet>>();
	do
	{
		Packet packet;
		sf::Socket::Status status = receiveTimeout(packet, receive_time - clock.getElapsedTime());
		if (status == sf::Socket::Done)
		{
			unsigned int program_id;
			packet.packet >> program_id;
			if (program_id == PROGRAM_ID)
				packets->push_back(packet);
		}
	} while (clock.getElapsedTime() < receive_time);
	return packets;
}

void Networking::sendSnapshot(World & world)
{
	// TODO: change
	sf::Packet packet;
	packet << PROGRAM_ID << TC_DEBUG_SET_POS;
	
	world.serializeSnapshot(packet);

	//std::cout << "SENDING: world snapshot\n";
	for (auto&& map_elem : clients)
	{
		Client client = map_elem.second;
		send(packet, client);
	}
}

void Networking::sendAddMob(ID mob_id, World & world)
{
	sf::Packet packet;
	packet << PROGRAM_ID << TC_ADD_MOB << mob_id;
	for (auto&& map_elem : clients)
	{
		send(packet, map_elem.second);
	}
}

void Networking::sendDropItem(Item item)
{
	sf::Packet packet;
	packet << PROGRAM_ID << TC_DROP_ITEM << item.getItemId() << item.getName() << item.getDescription()
		<< item.getSymbol();
	for (auto&& map_elem : clients)
	{
		send(packet, map_elem.second);
	}
}


void Networking::sendWorldState(World & world, Client client)
{
	sf::Packet packet;
	packet << PROGRAM_ID << TC_WORLD_STATE;
	world.serializeWorldState(packet);

	send(packet, client);
}

Client Networking::addClient(ID mob_id, sf::IpAddress ip, Port port)
{
	ID new_id = client_id_counter;
	client_id_counter++;

	Client client;
	client.id = new_id;
	client.address = ip;
	client.mob_id = mob_id;
	client.port = port;

	clients[new_id] = client;

	std::cout << "Client added\n\tid: " << client.id << "\n\tmob_id: " << client.mob_id << "\n\tip: " << client.address << "\n\tport: " << client.port << "\n";

	sf::Packet packet;
	packet << PROGRAM_ID << TC_CONFIRM_JOIN;
	packet << client.id << client.mob_id;

	send(packet, client);

	return client;
}

void Networking::removeClient(ID client_id, World & world)
{
	if (clients.count(client_id) > 0)
	{
		Client client = clients[client_id];

		// world.removeMob(client.mob_id);

		std::cout << "Removing client with id: " << client_id << "\n";

		clients.erase(client_id);

		sf::Packet packet;
		packet << PROGRAM_ID << TC_REMOVE_MOB;
		packet << client.mob_id;
		for (auto map_elem : clients)
		{
			send(packet, map_elem.second);
		}
	}
	else
	{
		std::cout << "Could not remove client with id: " << client_id << ", id not found\n";
	}
}

ID Networking::mobIDFromClientID(ID client_id)
{
	if (clients.count(client_id) > 0)
	{
		return clients[client_id].mob_id;
	}
	else
	{
		return ID_NOT_FOUND;
	}
}