
#include "engine.hpp"

#include "../../server/src/definitions.hpp"


Engine::Engine()
{
	test.bind(test.AnyPort);


	sf::IpAddress ip = "localhost";
	Port port = 8778;

	sf::Packet packet;
	packet << TS_JOIN_SERVER;

	test.send(packet, ip, port);
}

void Engine::update()
{
	

}

void Engine::render(sf::RenderTarget & target)
{
	renderer.drawString(15, 10, "Hello", sf::Color::Red);
	renderer.drawString(21, 10, "World", sf::Color::Green);
	renderer.drawString(26, 10, "!", sf::Color::Blue);




	target.draw(renderer);
	renderer.clear();
}