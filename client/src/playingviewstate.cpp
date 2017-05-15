#include "playingviewstate.hpp"

#include "engine.hpp"

#include "inventoryviewstate.hpp"

void PlayingViewState::init(Engine& engine)
{}

std::shared_ptr<PlayerViewState> PlayingViewState::update(Engine& engine)
{
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
		return std::make_shared<InventoryViewState>();
		
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) //temporary drop item thing, drops item with global id 0 aka. The Crazy Thing
	{
		//change view state
		engine.getNetworking().sendDropItem(0);
	}

	return nullptr;
}

PlayingViewState::~PlayingViewState()
{}
