#include "playingviewstate.hpp"

#include "engine.hpp"

#include "inventoryviewstate.hpp"
#include "input.hpp"

void PlayingViewState::init(Engine& engine)
{}

void PlayingViewState::windowEvent(sf::Event event, Engine& engine)
{

}

std::shared_ptr<PlayerViewState> PlayingViewState::update(Engine& engine)
{
	/*
	sf::Vector2i vel;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	vel.x += 1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	vel.x -= 1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	vel.y -= 1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	vel.y += 1;
	
	*/

	sf::Time walk_wait = sf::seconds(0.2);
	bool waited = walk_timer.getElapsedTime() > walk_wait;
	if((
		key::pressed(sf::Keyboard::Left) 
		|| key::pressed(sf::Keyboard::Right) 
		|| key::pressed(sf::Keyboard::Up) 
		|| key::pressed(sf::Keyboard::Down)) 
		&& !waited
		|| !key::down(sf::Keyboard::Left)
		&& !key::down(sf::Keyboard::Right)
		&& !key::down(sf::Keyboard::Up)
		&& !key::down(sf::Keyboard::Down))
		walk_timer.restart();
	
	sf::Vector2i vel;
	if (key::pressed(sf::Keyboard::Left) || key::down(sf::Keyboard::Left) && waited)
		vel.x -= 1;
	if (key::pressed(sf::Keyboard::Right) || key::down(sf::Keyboard::Right) && waited)
		vel.x += 1;
	if (key::pressed(sf::Keyboard::Up) || key::down(sf::Keyboard::Up) && waited)
		vel.y -= 1;
	if (key::pressed(sf::Keyboard::Down) || key::down(sf::Keyboard::Down) && waited)
		vel.y += 1;
	if (vel.y != 0 || vel.x != 0)
		engine.getNetworking().testMove(vel);


	if (key::pressed(sf::Keyboard::E))
	{
		engine.getNetworking().sendPickup();
	}
	if (key::pressed(sf::Keyboard::I))
	{
		//change view state
		return std::make_shared<InventoryViewState>();
	}

	return nullptr;
}

void PlayingViewState::render(World& world, Renderer& renderer)
{
	world.render(renderer);
}

PlayingViewState::~PlayingViewState()
{}
