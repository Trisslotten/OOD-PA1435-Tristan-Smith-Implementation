#pragma once

#include <unordered_map>
#include <SFML/Network.hpp>
#include <memory>
#include "client.hpp"
#include "world.hpp"
#include "../../shared/definitions.hpp"
#include "packet.hpp"

class Networking
{
	std::unordered_map<ID, Client> clients;

	ID client_id_counter = 0;

	sf::UdpSocket socket;

	void send(sf::Packet, Client client);
public:

	Networking(Port port); 
	Networking() = delete;

	std::shared_ptr< std::vector<Packet> > receive(sf::Time receive_time);

	void sendSnapshot(World& world);

	void addClient(ID mob_id, sf::IpAddress ip, Port port);

};