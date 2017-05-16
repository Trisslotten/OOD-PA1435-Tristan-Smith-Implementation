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

	void send(sf::Packet, Client);
	void send(sf::Packet, ID client_id);

	// use this instead of socket.receive(...)
	sf::Socket::Status receiveTimeout(Packet& packet, sf::Time timeout);
public:

	Networking(Port port); 
	Networking() = delete;
	~Networking();

	std::shared_ptr< std::vector<Packet> > receive(sf::Time receive_time);

	void sendSnapshot(World& world);

	void sendAddMob(ID mob_id, World& world);

	void sendMap(const Map& map, Client client);

	void sendAddItem();

	void sendDropItem(Item item);
	void sendGroundItem(Item item, Client client);

	void sendWorldState(World& world, Client client);

	// add a client to the map and return it
	Client addClient(ID mob_id, sf::IpAddress ip, Port port);

	void removeClient(ID client_id, World& world);

	ID mobIDFromClientID(ID client_id);

	void sendRemoveItemFromGround(ID id);

	void sendPickupProgress(bool success, ID client_id, std::string name);
	
	void sendInventory(Player player, ID client_id);

	void sendDescriptions(World& world, sf::Vector2i pos, ID client_id);

	void sendEquipped(Player player, ID client_id);

	void sendRemoveMob(ID mob_id);
};