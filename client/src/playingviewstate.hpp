#pragma once
#include "playerviewstate.hpp"
#include "inventoryviewstate.hpp"
class PlayingViewState : public PlayerViewState
{
public:
	virtual std::shared_ptr<PlayerViewState> update(Engine& engine);
	virtual void render(World& world, Renderer& renderer);
	virtual ~PlayingViewState();
};