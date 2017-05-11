#include <iostream>

#include "server.hpp"

int main(int argc, char *argv[])
{
	for (int i = 0; i < argc; i++)
	{
		std::cout << argv[i] << "\n";
	}




	float tick_rate = 30;

	Server server{ 8778 };

	sf::Clock timer;
	timer.restart();
	while (true)
	{
		server.update();

		server.receive(sf::seconds(1 / tick_rate) - timer.getElapsedTime());
		timer.restart();
	}

	system("pause");


	return 0;
}