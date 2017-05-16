#include <SFML/Graphics.hpp>

#include "engine.hpp"
#include <iostream>
#include "input.hpp"

int main()
{
	Engine engine;

	sf::Vector2i size = engine.getRenderer().getScreenSize();

	float fps = 60;
	sf::RenderWindow window(sf::VideoMode(size.x, size.y), "Hello World!");


	sf::Clock debug;
	int updates = 0;
	int frames = 0;

	sf::Time accum;
	sf::Clock update_timer;
	sf::Clock timer;
	timer.restart();
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			default:
				engine.windowEvent(event);
			}		
		}

		accum += update_timer.restart();
		while (accum > sf::seconds(1 / TICK_RATE))
		{
			key::update();
			// TODO: create seperate handleInput function
			if (window.hasFocus())
				engine.update();
			accum -= sf::seconds(1 / TICK_RATE);
			updates++;
		}
		frames++;

		engine.receive(sf::seconds(1 / fps) - timer.getElapsedTime());
		timer.restart();


		if (debug.getElapsedTime() > sf::seconds(1))
		{
			debug.restart();
			window.setTitle("FPS: " + std::to_string(frames) + " UPS: " + std::to_string(updates));
			frames = 0;
			updates = 0;
		}

		window.clear();
		engine.render(window);
		window.display();
	}
	//engine.getNetworking().disconnect();

	return 0;
}