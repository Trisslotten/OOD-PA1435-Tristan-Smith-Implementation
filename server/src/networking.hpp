#pragma once

#include <unordered_map>
#include <SFML/Network.hpp>
#include <memory>
#include "client.hpp"
#include "world.hpp"
#include "definitions.hpp"
#include "packet.hpp"

class Networking
{
	std::unordered_map<ID, Client> clients;

	ID client_id_counter = 0;

	sf::UdpSocket socket;

public:

	Networking(Port port); 
	Networking() = delete;

	std::shared_ptr< std::vector<Packet> > receive();

	void sendSnapshot(World& world);

	void addClient(ID mob_id, sf::IpAddress ip, Port port);

};