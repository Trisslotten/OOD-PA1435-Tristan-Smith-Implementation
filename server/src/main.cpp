#include <iostream>

#include "server.hpp"

#include "../../shared/definitions.hpp"

int main(int argc, char *argv[])
{
	Port port = SERVER_PORT;
	if (argc >= 2)
	{
		std::string str_port = argv[1];
		try
		{
			Port param_port = std::stoi(str_port, nullptr, 10);
			port = param_port;
		} catch (std::invalid_argument e)
		{
			std::cerr << "Parameter not a number. Using default port: " << port << "\n";
		}
	}
	std::cout << "Starting server on port: " << port << "\n";
	Server server{ port };

	server.init();

	sf::Clock debug_timer;

	sf::Clock timer;
	timer.restart();
	while (true)
	{
		debug_timer.restart();
		server.update();
		//std::cout << "Update:  " << debug_timer.restart().asMilliseconds() << "\n";


		server.receive(sf::seconds(1 / TICK_RATE) - timer.getElapsedTime());
		timer.restart();
		//std::cout << "Receive: " << debug_timer.restart().asMilliseconds() << "\n";
	}
	system("pause");

	return 0;
}