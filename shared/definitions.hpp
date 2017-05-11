#pragma once

#include <limits>

#define ID unsigned int
#define Port unsigned short

const ID ID_NOT_FOUND = std::numeric_limits<ID>::max();

const Port SERVER_PORT = 8778;

const unsigned int PROGRAM_ID = 2874393505;

// number of packets the server sends to a joining client
const unsigned int WORLD_STATE_PACKET_COUNT = 2;

enum PacketAction
{
	// TS: to server
	TS_JOIN_SERVER = 0,
	TS_DISCONNECT,

	TS_DEBUG_SEND_STRING,
	TS_DEBUG_MOVE,


	// TC: to client
	TC_CONFIRM_JOIN,
	TC_SERVER_SHUTDOWN,
	TC_ADD_MOB,
	TC_WORLD_STATE,

	TC_DEBUG_SEND_STRING,
	TC_DEBUG_SET_POS,



};
