#include "networking.hpp"

#include "../../shared/definitions.hpp"
#include <memory>
#include <iostream>



sf::Socket::Status Networking::receiveTimeout(sf::Packet & packet, sf::IpAddress & ip, Port & port, sf::Time timeout)
{
	sf::SocketSelector selector;
	selector.add(socket);
	if (selector.wait(timeout))
		return socket.receive(packet, ip, port);
	else
		return sf::Socket::NotReady;
}

Networking::Networking()
{}

Networking::~Networking()
{
	disconnect();
}

void Networking::setID(ID _client_id)
{
	client_id = _client_id;
}

ID Networking::getID()
{
	return client_id;
}

std::shared_ptr<std::vector<sf::Packet>> Networking::connect(sf::IpAddress _server_ip, Port _server_port)
{
	server_ip = _server_ip;
	server_port = _server_port;

	socket.bind(socket.AnyPort);

	sf::Packet packet;
	packet << PROGRAM_ID << TS_JOIN_SERVER;
	send(packet);

	socket.setBlocking(true);
	auto packets = std::make_shared<std::vector<sf::Packet>>();
	unsigned int num_packets = 0;

	sf::Clock timer;
	timer.restart();

	// really bad hack, hope that all packet arrive in time...
	while (timer.getElapsedTime() < sf::seconds(5));
	{
		sf::Packet packet;
		sf::IpAddress address;
		Port port;
		// use normal since time isnt important on connect
		// maybe change if client wait too long
		sf::Socket::Status status = socket.receive(packet, address, port);
		if (status == sf::Socket::Done)
		{
			unsigned int program_id;
			packet >> program_id;
			if (program_id == PROGRAM_ID)
			{
				packets->push_back(packet);
				num_packets++;
			}
		}
	}
	socket.setBlocking(false);
	return packets;
}

void Networking::disconnect()
{
	sf::Packet packet;
	packet << PROGRAM_ID << TS_DISCONNECT;
	packet << client_id;

	send(packet);
}





void Networking::send(sf::Packet packet)
{
	socket.send(packet, server_ip, server_port);
}




std::shared_ptr<std::vector<sf::Packet>> Networking::receive(sf::Time receive_time)
{
	auto packets = std::make_shared<std::vector<sf::Packet>>();

	sf::Clock clock;
	clock.restart();
	// TODO: set time as parameter
	do
	{
		sf::Packet packet;
		sf::IpAddress address;
		Port port;
		sf::Socket::Status status = receiveTimeout(packet, address, port, receive_time - clock.getElapsedTime());
		if (status == sf::Socket::Done)
		{
			unsigned int program_id;
			packet >> program_id;
			if (program_id == PROGRAM_ID)
				packets->push_back(packet);
		}
	} while (clock.getElapsedTime() < receive_time);

	return packets;
}

void Networking::testMove(sf::Vector2i vel)
{
	sf::Packet packet;
	packet << PROGRAM_ID << TS_MOVE_PLAYER;
	packet << client_id << vel.x << vel.y;
	std::cout << "SENDING: test move: " << vel.x << " " << vel.y << std::endl;
	send(packet);
}

void Networking::sendPickup()
{
	sf::Packet packet;
	packet << PROGRAM_ID << TS_PICKUP_ITEM << client_id;
	send(packet);
}

void Networking::sendRequestInventory()
{
	sf::Packet packet;
	packet << PROGRAM_ID << TS_REQUEST_INVENTORY << client_id;
	send(packet);
}

void Networking::sendRequestDescriptions(sf::Vector2i pos)
{
	sf::Packet packet;
	packet << PROGRAM_ID << TS_REQUEST_DESCRIPTIONS << client_id;
	packet << pos.x << pos.y;
	send(packet);
}

void Networking::sendDropItem(ID item_id)
{
	sf::Packet packet;
	packet << PROGRAM_ID << TS_DROP_ITEM << client_id << item_id;
	send(packet);
}