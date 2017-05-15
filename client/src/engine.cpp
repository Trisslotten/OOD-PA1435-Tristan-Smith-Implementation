
#include "engine.hpp"

#include "../../shared/definitions.hpp"
#include <sstream>

World & Engine::getWorld()
{
	return world;
}

Networking & Engine::getNetworking()
{
	return networking;
}

const Renderer & Engine::getRenderer() const
{
	return renderer;
}

Engine::Engine()
{

	auto packets = networking.connect("localhost", SERVER_PORT);
	packet_parser.parse(packets, *this);
}

void Engine::update()
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
	if(vel.y != 0 || vel.x != 0)
		networking.testMove(vel);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		networking.sendPickup();
	}
}

void Engine::receive(sf::Time receive_time)
{
	auto packets = networking.receive(receive_time);
	packet_parser.parse(packets, *this);
}

void Engine::render(sf::RenderTarget & target)
{

	world.render(renderer);
	
	target.draw(renderer);
	renderer.clear();
}