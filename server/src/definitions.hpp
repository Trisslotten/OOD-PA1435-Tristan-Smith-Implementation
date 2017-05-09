#pragma once


#define ID unsigned int
#define Port unsigned short

enum PacketAction
{	
	// TS = to server
	TS_JOIN_SERVER = 0,
	TS_DISCONNECT,

	// TC = to client
	TC_CONFIRM_JOIN,
	TC_SERVER_SHUTDOWN
};
