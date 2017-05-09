#include "packetparser.hpp"

#include <SFML/Network.hpp>
#include "definitions.hpp"
#include "packet.hpp"


void PacketParser::joinServer(Packet& packet, Networking & networking, World & world)
{
	//ID mob_id = world.createPlayer();

	networking.addClient(0, packet.address, packet.port);
}

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

			break;
		default:
			// error message?
			break;
		}
	}
}
