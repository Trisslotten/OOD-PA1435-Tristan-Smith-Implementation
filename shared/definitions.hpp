#pragma once


#define ID unsigned int
#define Port unsigned short

const Port SERVER_PORT = 8778;

const unsigned int PROGRAM_ID = 2874393505;

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

	TC_DEBUG_SEND_STRING,
	TC_DEBUG_SET_POS,



};
