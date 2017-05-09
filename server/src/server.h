#pragma once


#include "networking.hpp"
#include "packetparser.hpp"

class Server
{
	Networking networking;
	PacketParser packet_parser;
	World world;
public: 

	Server(Port port) : networking(port) 
	{}

	void update();

};