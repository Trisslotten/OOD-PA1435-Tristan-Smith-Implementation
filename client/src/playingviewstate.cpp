#include "playingviewstate.hpp"

#include "engine.hpp"

std::shared_ptr<PlayerViewState> PlayingViewState::update(Engine& engine)
{
	PlayerViewState* returnstate = nullptr;
	sf::Vector2i vel;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		vel.x += 1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		vel.x -= 1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		vel.y -= 1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		vel.y += 1;
	if (vel.y != 0 || vel.x != 0)
		engine.getNetworking().testMove(vel);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		engine.getNetworking().sendPickup();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
	{
		//change view state
		engine.getNetworking().sendRequestInventory();
		InventoryViewState* invstate = new InventoryViewState();
		returnstate = invstate;
	}

	return (std::shared_ptr<PlayerViewState>)returnstate;
}

void PlayingViewState::render(World& world, Renderer& renderer)
{
	world.render(renderer);
}

PlayingViewState::~PlayingViewState()
{}
