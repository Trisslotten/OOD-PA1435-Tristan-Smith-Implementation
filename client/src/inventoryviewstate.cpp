#include "inventoryviewstate.hpp"

#include "engine.hpp"

void InventoryViewState::init(Engine& engine)
{
	engine.getNetworking().sendRequestInventory();
}

std::shared_ptr<PlayerViewState> InventoryViewState::update(Engine & engine)
{

	return nullptr;
}

InventoryViewState::~InventoryViewState()
{}
