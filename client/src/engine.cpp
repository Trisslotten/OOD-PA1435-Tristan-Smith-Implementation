
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

Engine::Engine()
{

	networking.connect("localhost", SERVER_PORT);
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


}

void Engine::receive(sf::Time receive_time)
{
	auto packets = networking.receive(receive_time);
	packet_parser.parse(packets, *this);
}

void Engine::render(sf::RenderTarget & target)
{
	int x = test_pos.x;
	int y = test_pos.y;
	renderer.drawString(x, y, "Hello", sf::Color::Red);
	renderer.drawString(x+6, y, "World", sf::Color::Green);
	renderer.drawString(x+11, y, "!", sf::Color::Blue);

	

	std::string text = " ######           ###################\n##....##          #.................#\n#......############.................#\n#...................................#\n#......############.................#\n##....##          #.............#####\n ######           #.............#\n                  #.............#\n                  ###############";
	std::stringstream sstream(text);
	std::string line;
	int i = 0;
	while (std::getline(sstream, line, '\n'))
	{
		renderer.drawString(x, y + i + 2, line);
		i++;
	}
	

	target.draw(renderer);
	renderer.clear();
}