#pragma once
#include "playerviewstate.hpp"
class PlayingViewState : public PlayerViewState
{
public:
	virtual PlayerViewState update(Engine* engine);
};