#pragma once
#include "playerviewstate.hpp"
#include "playingviewstate.hpp"

class InventoryViewState : public PlayerViewState
{
private:
	int currentItem = 0;
	int page = 0;
public:
	virtual std::shared_ptr<PlayerViewState> update(Engine& engine);
	virtual void render(World& world, Renderer& renderer);
	virtual ~InventoryViewState();
};