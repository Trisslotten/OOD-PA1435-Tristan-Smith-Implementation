#include "packetparser.hpp"

#include <SFML/Network.hpp>
#include "../../shared/definitions.hpp"
#include "packet.hpp"

#include <iostream>


void PacketParser::parse(std::shared_ptr<std::vector<Packet>> packets, Networking & networking, World & world)
{
	for (auto&& p : *packets)
	{
		unsigned int action;
		p.packet >> action;
		switch (action)
		{
		case TS_JOIN_SERVER:
			joinServer(p, networking, world);
			break;
		case TS_DISCONNECT:
			disconnectClient(p, networking, world);
			break;
		case TS_DEBUG_MOVE:
			debugMove(p, networking, world);
			break;
		case TS_DROP_ITEM:
			dropItem(p, networking, world);
			break;
		default:
			// error message?
			break;
		}
	}
}


void PacketParser::joinServer(Packet& packet, Networking & networking, World & world)
{
	ID mob_id = world.createPlayer();

	networking.sendAddMob(mob_id, world);

	Client client = networking.addClient(mob_id, packet.address, packet.port);
	networking.sendWorldState(world, client);
}

void PacketParser::disconnectClient(Packet & packet, Networking & networking, World & world)
{
	ID client_id;
	packet.packet >> client_id;
	ID mob_id = networking.mobIDFromClientID(client_id);
	if (mob_id != ID_NOT_FOUND)
	{
		world.removePlayer(mob_id);
		networking.removeClient(client_id, world);
	}
}


void PacketParser::debugMove(Packet & packet, Networking & networking, World & world)
{
	ID client_id;
	sf::Vector2i vel;
	packet.packet >> client_id >> vel.x >> vel.y;
	std::cout << "RECEIVE: test move id: " << client_id << ", " << vel.x << " " << vel.y << "\n";

	ID mob_id = networking.mobIDFromClientID(client_id);
	if (mob_id != ID_NOT_FOUND)
	{
		world.movePlayer(mob_id, vel);
	}
}

void PacketParser::dropItem(Packet& packet, Networking & networking, World & world)
{
	ID client_id;
	ID item_id;
	packet.packet >> client_id >> item_id;
	std::cout << "RECEIVE: drop item id: " << client_id << "\n";
	ID mob_id = networking.mobIDFromClientID(client_id);
	if (mob_id != ID_NOT_FOUND)
	{
		Player* player = world.getPlayerById(mob_id);
		player->removeItem(item_id);
		Item theitem = player->getItemById(item_id);
		world.placeItemOnGround(theitem);
		networking.sendDropItem(theitem);
	}
}