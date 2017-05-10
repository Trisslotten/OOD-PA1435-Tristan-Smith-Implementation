#pragma once

#include <SFML/Network.hpp>
#include "../../shared/definitions.hpp"
#include <memory>

class Networking
{
	sf::IpAddress server_ip;
	Port server_port;

	// id assigned to this client from the server
	ID client_id;

	sf::UdpSocket socket;
public:

	Networking();
	~Networking();

	void setID(ID _client_id);

	void connect(sf::IpAddress server_ip, Port server_port);
	void disconnect();

	void send(sf::Packet packet);

	std::shared_ptr< std::vector<sf::Packet>> receive(sf::Time receive_time);

	void testMove(sf::Vector2i vel);

	//void sendSnapshot(World& world);

};