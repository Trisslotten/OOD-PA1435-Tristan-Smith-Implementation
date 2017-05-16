#pragma once

#include <memory>

#include "playerviewstate.hpp"

#include "renderer.hpp"

class World;

class PointerViewState : public PlayerViewState
{
	//std::vector

	// (0,0) is center of screen, world pos is player pos + pointer_pos
	sf::Vector2i pointer_pos;

	sf::Clock walk_timer;
public:
	virtual void init(Engine& engine);
	virtual void windowEvent(sf::Event event, Engine& engine);
	virtual std::shared_ptr<PlayerViewState> update(Engine& engine);
	virtual void render(World& world, Renderer& renderer);
	virtual ~PointerViewState();
};