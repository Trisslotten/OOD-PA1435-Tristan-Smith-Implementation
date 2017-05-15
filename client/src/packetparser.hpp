#pragma once

#include <SFML/Network.hpp>
#include <memory>
#include <vector>

class Engine;
class World;

class PacketParser
{

	void debugMove(sf::Packet & packet, Engine & engine);


	void confirmJoin(sf::Packet & packet, Engine & engine);
	void addMob(sf::Packet packet, Engine& engine);
	void removeMob(sf::Packet packet, Engine& engine);
	void parseWorldState(sf::Packet packet, Engine& engine);
	void parseMapSize(sf::Packet packet, Engine& engine);
	void parseMapChunk(sf::Packet packet, Engine& engine);


	void serverShutdown(Engine& engine);
public:

	void parse(std::shared_ptr<std::vector<sf::Packet>> packets, Engine & engine);

};