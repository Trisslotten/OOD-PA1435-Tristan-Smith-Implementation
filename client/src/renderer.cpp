#include "renderer.hpp"

#include <iostream>

Renderer::Renderer()
{
	if (!tileset.loadFromFile("tileset.png"))
	{
		std::cerr << "Could not load tileset\n";
	}
	std::cout << "SUCCESS" << std::endl;
	tiles.resize(screen_height_tiles*screen_width_tiles);
	tiles_colors.resize(screen_height_tiles*screen_width_tiles);
	clear();
}

void Renderer::clear()
{
	clear(0);
}

void Renderer::clear(char symbol)
{
	for (int i = 0; i < tiles.size(); i++)
	{
		tiles[i] = symbol;
		tiles_colors[i] = sf::Color::White;
	}
}


void Renderer::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	sf::Sprite sprite;
	sprite.setTexture(tileset);
	for (int i = 0; i < screen_height_tiles; i++)
	{
		for (int j = 0; j < screen_width_tiles; j++)
		{
			unsigned char current_tile = tiles[j + i*screen_width_tiles];
			int x_index = current_tile % tileset_width;
			int y_index = current_tile / tileset_height;

			sf::IntRect rect;
			rect.left = x_index * tile_size;
			rect.width = tile_size;
			rect.top = y_index * tile_size;
			rect.height = tile_size;
			sprite.setTextureRect(rect);

			sprite.setPosition(j*tile_size, i*tile_size);

			sf::Color current_color = tiles_colors[j + i*screen_width_tiles];
			sprite.setColor(current_color);
			target.draw(sprite);
		}
	}
}

void Renderer::drawChar(int x, int y, unsigned char symbol, sf::Color color)
{
	if (x < 0 || x >= screen_width_tiles || y < 0 || y >= screen_height_tiles)
	{
		return;
	}
	tiles[x + y*screen_width_tiles] = symbol;
	tiles_colors[x + y*screen_width_tiles] = color;
}

void Renderer::drawChar(sf::Vector2i pos, unsigned char symbol, sf::Color color)
{
	drawChar(pos.x, pos.y, symbol, color);
}

void Renderer::drawString(int x, int y, const std::string & str, sf::Color color)
{
	for (int i = 0; i < str.size(); i++)
	{
		drawChar(x + i, y, str[i], color);
	}
}

void Renderer::drawString(sf::Vector2i pos, const std::string & str, sf::Color color)
{
	drawString(pos.x, pos.y, str, color);
}
