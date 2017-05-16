#include <SFML/Graphics.hpp>

#include "engine.hpp"
#include <iostream>
#include "input.hpp"

int main(int argc, char *argv[])
{
	sf::IpAddress ip = "localhost";
	Port port = SERVER_PORT;
	if (argc >= 2)
	{
		ip = argv[1];
		if (ip == sf::IpAddress::None)
		{
			std::cerr << "Not a valid ip: " << argv[1] << ", Parsed as: " << ip.toString() << "\n";
			std::cerr << "Exiting";
			exit(EXIT_FAILURE);
		}
	}
	if (argc >= 3)
	{
		std::string str_port = argv[1];
		try
		{
			Port param_port = std::stoi(str_port, nullptr, 10);
			port = param_port;
		} catch (std::invalid_argument e)
		{
			std::cerr << "Not a valid port: " << argv[2] << ", Using default port: " << port << "\n";
		}
	}
	else
	{
		std::cout << "Using default port: " << port << "\n";
	}

	Engine engine(ip, port);

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