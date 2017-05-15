#pragma once
#include "playerviewstate.hpp"
class InventoryViewState : public PlayerViewState
{
public:
	virtual void init(Engine& engine);
	virtual std::shared_ptr<PlayerViewState> update(Engine& engine);
	virtual ~InventoryViewState();
};