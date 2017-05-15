#include "packetparser.hpp"

#include <iostream>

#include "../../shared/definitions.hpp"
#include <SFML/Network.hpp>
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
		case TC_DROP_ITEM:
			dropItem(packet, engine);
			break;
		case TC_REMOVE_ITEM:
			removeItem(packet, engine);
			break;
		case TC_PICKUP_SUCCESS:
			pickupSuccess(packet, engine);
		case TC_PICKUP_FAILED:
			pickupFailed(packet, engine);
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

	Map& map = engine.getWorld().getMap();
	int width, height;
	packet >> width >> height;
	map.setSize(width, height);
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			Tile t;
			packet >> (sf::Int8&)t;
			map.setTileAt(j, i, t);
		}
	}
}

void PacketParser::serverShutdown(Engine & engine)
{
	// show disconnect message or something
}

void PacketParser::dropItem(sf::Packet packet, Engine & engine)
{
	ID id; std::string name; std::string description; int isymbol; unsigned int x; unsigned int y; sf::Uint8 r, g, b, a;
	packet >> id >> name >> description >> isymbol >> x >> y >> r >> g >> b >> a;
	char symbol = (char)isymbol;

	Item new_item(id, name, description, symbol, sf::Vector2i(x,y),sf::Color(r,g,b,a));
	engine.getWorld().addItem(new_item);
	std::cout << "RECEIVE: dropped item name: " << name << ", x: "<< x << ", y:" << y << ", r:" << r << ", g:" << g << ", b:" << b << "\n";
}

void PacketParser::removeItem(sf::Packet packet, Engine& engine)
{
	ID id;
	packet >> id;
	engine.getWorld().removeItem(id);
}

void PacketParser::pickupSuccess(sf::Packet packet, Engine& engine)
{
	std::string name;
	packet >> name;
	std::cout << "Succesfully picked up item: " << name << "/n";
}

void PacketParser::pickupFailed(sf::Packet packet, Engine& engine)
{
	std::cout << "Failed to pick up item" << "/n";
}