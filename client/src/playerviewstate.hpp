#pragma once

#include <memory>
#include "renderer.hpp"
#include "world.hpp"

class Engine;


class PlayerViewState
{
public:
	virtual void init(Engine& engine) = 0;
	virtual void windowEvent(sf::Event event, Engine& engine) = 0;
	virtual std::shared_ptr<PlayerViewState> update(Engine& engine) = 0;
	virtual void render(World& world, Renderer& renderer) = 0;
	virtual ~PlayerViewState() {}
};