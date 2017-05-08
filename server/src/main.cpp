#include <iostream>

#include "server.h"

int main(int argc, char *argv[])
{

	for (int i = 0; i < argc; i++)
	{
		std::cout << argv[i] << "\n";
	}

	Server server{ 8778 };

	while (true)
	{
		server.update();
	}

	system("pause");


	return 0;
}