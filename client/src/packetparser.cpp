#include "packetparser.hpp"

#include <iostream>

#include "../../shared/definitions.hpp"

#include "engine.hpp"
#include "world.hpp"

void PacketParser::parse(std::shared_ptr<std::vector<sf::Packet>> packets, Engine & engine)
{
	for (auto&& packet : *packets)
	{
		int action;
		packet >> action;


		std::string msg;
		switch (action)
		{
		case TC_CONFIRM_JOIN:
			confirmJoin(packet, engine);
			break;
		case TC_DEBUG_SEND_STRING:
			packet >> msg;
			std::cout << msg << "\n";
			break;
		case TC_SERVER_SHUTDOWN:
			serverShutdown(engine);
			break;
		case TC_REMOVE_MOB:
			removeMob(packet, engine);
			break;
		case TC_ADD_MOB:
			addMob(packet, engine);
			break;
		case TC_WORLD_STATE:
			parseWorldState(packet, engine);
			break;
		case TC_DEBUG_SET_POS:
			debugMove(packet, engine);
			break;
		default:
			// error message?
			break;
		}
	}
}


void PacketParser::debugMove(sf::Packet & packet, Engine & engine)
{
	size_t num_players;
	packet >> num_players;
	for (int i = 0; i < num_players; i++)
	{
		ID mob_id;
		sf::Vector2i pos;
		packet >> mob_id >> pos.x >> pos.y;
		engine.getWorld().setMobPos(mob_id, pos);
	}
	//std::cout << "RECEIVE: test move" << engine.test_pos.x << " " << engine.test_pos.y << "\n";
}

void PacketParser::confirmJoin(sf::Packet & packet, Engine & engine)
{
	ID client_id, mob_id;
	packet >> client_id >> mob_id;
	engine.getNetworking().setID(client_id);
	engine.getWorld().setPlayerID(mob_id);

	std::cout << "RECEIVE: confirm join, client_id: " << client_id << "\n";
}

void PacketParser::addMob(sf::Packet packet, Engine & engine)
{
	ID mob_id;
	packet >> mob_id;
	engine.getWorld().addMob(mob_id, sf::Vector2i());
	std::cout << "Adding mob:\n\tmob_id: " << mob_id << "\n\tpos: " << 0 << ", " << 0 << "\n";
}

void PacketParser::removeMob(sf::Packet packet, Engine & engine)
{
	ID mob_id;
	packet >> mob_id;
	engine.getWorld().removeMob(mob_id);
}

void PacketParser::parseWorldState(sf::Packet packet, Engine & engine)
{
	size_t num_players;
	packet >> num_players;
	std::cout << "Mobs to add: " << num_players << "\n";
	for (int i = 0; i < num_players; i++)
	{
		ID mob_id;
		sf::Vector2i pos;
		packet >> mob_id;
		packet >> pos.x >> pos.y;
		engine.getWorld().addMob(mob_id, pos);

		//std::cout << "Adding mob:\n\tmob_id: " << mob_id << "\n\tpos: " << pos.x << ", " << pos.y << "\n";
	}
}

void PacketParser::serverShutdown(Engine & engine)
{
	// show disconnect message or something
}
