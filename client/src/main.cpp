#include <SFML/Graphics.hpp>

#include "engine.hpp"

int main()
{
	Engine engine;

	float fps = 30;
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Hello World!");


	sf::Clock timer;
	timer.restart();
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		// TODO: create seperate handleInput function
		if(window.hasFocus())
			engine.update();

		engine.receive(sf::seconds(1 / fps) - timer.getElapsedTime());
		timer.restart();

		window.clear();
		engine.render(window);
		window.display();
	}
	engine.getNetworking().disconnect();

	return 0;
}