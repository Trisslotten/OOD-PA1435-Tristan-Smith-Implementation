#pragma once

#include <SFML/Network.hpp>
#include "../../shared/definitions.hpp"
#include <memory>

class Networking
{
	struct Server
	{
		sf::IpAddress ip;
		Port port;
	} server;
	

	sf::UdpSocket socket;

public:

	Networking();

	void connect(sf::IpAddress server_ip, Port server_port);

	void send(sf::Packet packet);

	std::shared_ptr< std::vector<sf::Packet>> receive(sf::Time receive_time);

	void testMove(sf::Vector2i vel);

	//void sendSnapshot(World& world);

};