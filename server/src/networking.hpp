#pragma once

#include <unordered_map>
#include <SFML/Network.hpp>
#include <memory>
#include "client.hpp"
#include "world.hpp"

class Networking
{
	std::unordered_map<unsigned int, Client> clients;

	sf::UdpSocket socket;

public:

	Networking(unsigned short port); 
	Networking() = delete;

	std::shared_ptr< std::vector<sf::Packet> > receive();

	void sendSnapshot(World& world);

};