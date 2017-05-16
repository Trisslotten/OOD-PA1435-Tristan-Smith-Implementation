#include <iostream>

#include "server.hpp"

#include "../../shared/definitions.hpp"

int main(int argc, char *argv[])
{
	for (int i = 0; i < argc; i++)
	{
		std::cout << argv[i] << "\n";
	}

	Server server{ 8778 };

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