#pragma once
#include "engine.hpp"

class PlayerViewState
{
public:
	virtual PlayerViewState update(Engine* engine) {}
	PlayerViewState() {}
};