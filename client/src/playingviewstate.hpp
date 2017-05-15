#pragma once
#include "playerviewstate.hpp"

class PlayingViewState : public PlayerViewState
{
public:
	virtual std::shared_ptr<PlayerViewState> update(Engine& engine);
	virtual ~PlayingViewState();
};