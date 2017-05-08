#include "engine.hpp"


void Engine::update()
{}

void Engine::render(sf::RenderTarget & target)
{
	renderer.drawString(35, 20, "Hello World!");

	target.draw(renderer);
	renderer.clear();
}