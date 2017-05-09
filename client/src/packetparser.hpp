#pragma once

#include <SFML/Network.hpp>
#include <memory>
#include <vector>

class Engine;
class World;

class PacketParser
{

	void debugMove(sf::Packet & packet, Engine & engine, World& world);
public:

	void parse(std::shared_ptr<std::vector<sf::Packet>> packets, Engine & engine, World & world);

};