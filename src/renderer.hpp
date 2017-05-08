#pragma once

#include <string>

#include <SFML/Graphics.hpp>

class Renderer : public sf::Drawable
{
	unsigned int tile_size = 16;
	unsigned int tileset_width = 16;
	unsigned int tileset_height = 16;


	unsigned int screen_width_tiles = 1280 / tile_size;
	unsigned int screen_height_tiles = 720 / tile_size;

	std::string tileset_path;

	sf::Texture tileset;

	std::vector<unsigned char> tiles;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:

	Renderer();

	void clear();

	void drawTile(int x, int y, unsigned char symbol);

	void drawString(int x, int y, const std::string& str);

};