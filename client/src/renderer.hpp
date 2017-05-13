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
	std::vector<sf::Color> tiles_colors;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:

	Renderer();

	void clear();
	void clear(char symbol);
	
	void drawChar(int x, int y, unsigned char symbol, sf::Color color = sf::Color::White);
	void drawChar(sf::Vector2i pos, unsigned char symbol, sf::Color color = sf::Color::White);

	void drawString(int x, int y, const std::string& str, sf::Color color = sf::Color::White);
	void drawString(sf::Vector2i pos, const std::string& str, sf::Color color = sf::Color::White);


	inline sf::Vector2i getScreenSize() const
	{
		return int(tile_size)*sf::Vector2i(screen_width_tiles, screen_height_tiles);
	}

	inline sf::Vector2i getScreenSizeTiles() const
	{
		return sf::Vector2i(screen_width_tiles, screen_height_tiles);
	}
};