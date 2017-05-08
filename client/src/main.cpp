#include <SFML/Graphics.hpp>

#include "engine.hpp"

int main()
{
	Engine engine;

	sf::RenderWindow window(sf::VideoMode(1280, 720), "Hello World!");


	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		engine.update();

		window.clear();
		engine.render(window);
		window.display();
	}

	return 0;
}