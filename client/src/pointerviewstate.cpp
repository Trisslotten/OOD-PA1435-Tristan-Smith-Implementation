#include "pointerviewstate.hpp"

#include "playerviewstate.hpp"
#include "playingviewstate.hpp"
#include "input.hpp"
#include "world.hpp"
#include "engine.hpp"

void PointerViewState::init(Engine & engine)
{
	
}

void PointerViewState::windowEvent(sf::Event event, Engine & engine)
{}

std::shared_ptr<PlayerViewState> PointerViewState::update(Engine & engine)
{
	sf::Time walk_wait = sf::seconds(0.2);
	bool waited = walk_timer.getElapsedTime() > walk_wait;
	if ((
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
	pointer_pos += vel;


	if (key::pressed(sf::Keyboard::V))
	{
		return std::make_shared<PlayingViewState>();
	}


	return nullptr;
}

void PointerViewState::render(World & world, Renderer & renderer)
{
	world.render(renderer);

	sf::Vector2i size = renderer.getScreenSizeTiles();

	renderer.drawChar(pointer_pos + size / 2, 12*16+5, sf::Color(255,255,50));


}

PointerViewState::~PointerViewState()
{}
