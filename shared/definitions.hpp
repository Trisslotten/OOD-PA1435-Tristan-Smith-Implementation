#pragma once

#include <limits>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#define ID unsigned int
#define Port unsigned short

const ID ID_NOT_FOUND = std::numeric_limits<ID>::max();

const Port SERVER_PORT = 8778;

const unsigned int PROGRAM_ID = 2874393505;

// number of packets the server sends to a joining client
const unsigned int WORLD_STATE_PACKET_COUNT = 2;

enum Tile : sf::Int8
{
	TILE_NOTHING,
	TILE_GROUND,
	TILE_WALL,
	NUM_TILES,
};

enum PacketAction
{
	// TS: to server
	TS_JOIN_SERVER = 0,
	TS_DISCONNECT,
	TS_DROP_ITEM,
	TS_PICKUP_ITEM,

	TS_DEBUG_SEND_STRING,
	TS_DEBUG_MOVE,


	// TC: to client
	TC_CONFIRM_JOIN,
	TC_SERVER_SHUTDOWN,
	TC_ADD_MOB,
	TC_REMOVE_MOB,
	TC_WORLD_STATE,
	TC_DROP_ITEM,
<<<<<<< HEAD
	TC_REMOVE_ITEM,
	TC_ADD_ITEM_TO_INVENTORY,
	TC_PICKUP_SUCCESS,
	TC_PICKUP_FAILED,
=======
	TC_MAP_SIZE,
	TC_MAP_CHUNK,
>>>>>>> origin/master

	TC_DEBUG_SEND_STRING,
	TC_DEBUG_SET_POS,
};

#define QUALITY_COMMON sf::Color(200, 200, 200, 255)
#define QUALITY_UNCOMMON sf::Color(0, 200, 0, 255)
#define QUALITY_RARE sf::Color(0, 0, 200, 255)
#define QUALITY_EPIC sf::Color(200, 0, 200, 255)
#define QUALITY_LEGENDARY sf::Color(200, 50, 0, 255)
