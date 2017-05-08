#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include "renderer.hpp"



class Engine
{
	Renderer renderer;


	sf::UdpSocket test;

public:

	Engine();

	void update();

	void render(sf::RenderTarget& target);

};