#include "networking.hpp"

#include <memory>
#include <iostream>


Networking::Networking()
{}

void Networking::connect(sf::IpAddress server_ip, Port server_port)
{
	server.ip = server_ip;
	server.port = server_port;

	socket.bind(socket.AnyPort);
	socket.setBlocking(false);

	sf::Packet packet;
	packet << PROGRAM_ID << TS_JOIN_SERVER;
	send(packet);
}

void Networking::send(sf::Packet packet)
{
	socket.send(packet, server.ip, server.port);
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
		sf::Socket::Status status = socket.receive(packet, address, port);
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
	packet << PROGRAM_ID << TS_DEBUG_MOVE;
	packet << vel.x << vel.y;
	std::cout << "SENDING: test move: " << vel.x << " " << vel.y << std::endl;
	send(packet);
}
