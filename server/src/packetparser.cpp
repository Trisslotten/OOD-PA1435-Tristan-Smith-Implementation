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
		case TS_MOVE_PLAYER:
			parseMovePlayer(p, networking, world);
			break;
		case TS_DROP_ITEM:
			dropItem(p, networking, world);
			break;
		case TS_PICKUP_ITEM:
			pickupItem(p, networking, world);
			break;
		case TS_REQUEST_INVENTORY:
			requestInventory(p, networking, world);
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
	for (auto&& map_elem : world.getItems())
	{
		networking.sendGroundItem(map_elem.second, client);
	}
	networking.sendMap(world.getMap(), client);
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


void PacketParser::parseMovePlayer(Packet & packet, Networking & networking, World & world)
{
	ID client_id;
	sf::Vector2i vel;
	packet.packet >> client_id >> vel.x >> vel.y;
	//std::cout << "RECEIVE: test move id: " << client_id << ", " << vel.x << " " << vel.y << "\n";

	ID mob_id = networking.mobIDFromClientID(client_id);
	if (mob_id != ID_NOT_FOUND)
	{
		auto pos = world.getPlayerById(mob_id)->getPos();
		if (!world.getMap().isWallAt(pos + vel))
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
		if (player->getInventory().count(item_id) > 0)
		{
			Item theitem = player->getItemById(item_id);
			theitem.setPos(player->getPos());
			player->removeItem(item_id);
			world.placeItemOnGround(theitem);
			networking.sendDropItem(theitem);
		}
	}
}

void PacketParser::pickupItem(Packet& packet, Networking& networking, World& world)
{
	ID client_id;
	packet.packet >> client_id;
	ID mob_id = networking.mobIDFromClientID(client_id);
	if (mob_id != ID_NOT_FOUND)
	{
		Player* player = world.getPlayerById(mob_id);
		ID item_id = world.getItemAtPos(player->getPos());
		bool picked = false;
		std::string name = "";
		if(item_id != ID_NOT_FOUND)
		{
			name = world.getItemById(item_id).getName();
			//remove from ground and place in player inventory on server
			world.pickupItemFromGround(player, item_id);
			//send remove from ground packet to all players
			networking.sendRemoveItemFromGround(item_id);
			picked = true;
		}
		networking.sendPickupProgress(picked, client_id, name);
	}
}

void PacketParser::requestInventory(Packet& packet, Networking& networking, World& world)
{
	ID client_id;
	packet.packet >> client_id;
	ID mob_id = networking.mobIDFromClientID(client_id);
	if (mob_id != ID_NOT_FOUND)
	{
		Player* player = world.getPlayerById(mob_id);
		networking.sendInventory(*player, client_id);
	}
}