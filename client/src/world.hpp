#pragma once

#include <unordered_map>

#include "../../shared/definitions.hpp"

// testing, remove later!
struct TestMob
{
	ID id;
	sf::Vector2i pos;
};


class World
{


public:

	std::unordered_map<ID, TestMob> test_mobs;

};