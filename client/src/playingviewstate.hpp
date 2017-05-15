#pragma once
#include "playerviewstate.hpp"

class PlayingViewState : public PlayerViewState
{
public:
	virtual void init(Engine& engine);
	virtual std::shared_ptr<PlayerViewState> update(Engine& engine);
	virtual ~PlayingViewState();
};