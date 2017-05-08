#include "engine.hpp"


void Engine::update()
{}

void Engine::render(sf::RenderTarget & target)
{
	renderer.drawString(15, 10, "Hello", sf::Color::Red);
	renderer.drawString(21, 10, "World", sf::Color::Green);
	renderer.drawString(26, 10, "!", sf::Color::Blue);

	target.draw(renderer);
	renderer.clear();
}