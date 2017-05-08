#include "engine.hpp"


Engine::Engine()
{
	test.bind(test.AnyPort);
}

void Engine::update()
{
	
	sf::IpAddress ip = "localhost";
	unsigned short port = 8778;

	std::string message = "NU SKICKAR VI HÄR JA";

	sf::Packet packet;
	packet << message;

	test.send(packet, ip, port);

}

void Engine::render(sf::RenderTarget & target)
{
	renderer.drawString(15, 10, "Hello", sf::Color::Red);
	renderer.drawString(21, 10, "World", sf::Color::Green);
	renderer.drawString(26, 10, "!", sf::Color::Blue);




	target.draw(renderer);
	renderer.clear();
}