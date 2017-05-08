#pragma once

#include <SFML/Graphics.hpp>

#include "renderer.hpp"



class Engine
{
	Renderer renderer;

public:
	void update();

	void render(sf::RenderTarget& target);

};