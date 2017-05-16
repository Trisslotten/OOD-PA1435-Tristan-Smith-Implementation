#pragma once
#include "playerviewstate.hpp"
#include "inventoryviewstate.hpp"
class PlayingViewState : public PlayerViewState
{

	sf::Clock walk_timer;
public:
	virtual void init(Engine& engine);
	virtual void windowEvent(sf::Event event, Engine& engine);
	virtual std::shared_ptr<PlayerViewState> update(Engine& engine);
	virtual void render(World& world, Renderer& renderer);
	virtual ~PlayingViewState();
};