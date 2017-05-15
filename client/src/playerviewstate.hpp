#pragma once

#include <memory>

class Engine;

class PlayerViewState
{
public:
	virtual void init(Engine& engine) = 0;
	virtual std::shared_ptr<PlayerViewState> update(Engine& engine) = 0;
	virtual ~PlayerViewState() {}
};