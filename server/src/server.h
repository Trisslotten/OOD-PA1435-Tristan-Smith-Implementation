#pragma once


#include "networking.hpp"

class Server
{
	Networking networking;
	
public: 

	Server(unsigned short port) : networking(port) 
	{}

	void update();

};