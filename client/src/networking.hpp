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

	// set the id this client has on the server
	void setID(ID _client_id);
	ID getID();

	// connects to a server and returns packets with world state data
	std::shared_ptr<std::vector<sf::Packet>> connect(sf::IpAddress server_ip, Port server_port);

	// send disconnect message to server
	void disconnect();

	// send param packet to server
	void send(sf::Packet packet);

	// receives packets for a time of "receive_time" and returns those
	std::shared_ptr< std::vector<sf::Packet>> receive(sf::Time receive_time);

	void testMove(sf::Vector2i vel);
};