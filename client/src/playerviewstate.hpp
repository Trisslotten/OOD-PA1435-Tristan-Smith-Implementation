#pragma once

#include <memory>

class Engine;

class PlayerViewState
{
public:
	virtual std::shared_ptr<PlayerViewState> update(Engine& engine) = 0;
	virtual ~PlayerViewState() {}
};