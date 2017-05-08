#include "renderer.hpp"

#include <iostream>

Renderer::Renderer()
{
	if (!tileset.loadFromFile("tileset.png"))
	{
		std::cerr << "Could not load tileset\n";
	}

	tiles.resize(screen_height_tiles*screen_width_tiles);
	clear();
}

void Renderer::clear()
{
	for (auto&& tile : tiles)
		tile = 0;
}


void Renderer::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	sf::Sprite sprite;
	sprite.setTexture(tileset);
	for (int i = 0; i < screen_height_tiles; i++)
	{
		for (int j = 0; j < screen_width_tiles; j++)
		{
			unsigned char current = tiles[j + i*screen_width_tiles];
			int x_index = current % tileset_width;
			int y_index = current / tileset_height;
			sf::IntRect rect;
			rect.left = x_index * tile_size;
			rect.width = tile_size;
			rect.top = y_index * tile_size;
			rect.height = tile_size;
			sprite.setTextureRect(rect);
			sprite.setPosition(j*tile_size, i*tile_size);
			target.draw(sprite);
		}
	}
}

void Renderer::drawTile(int x, int y, unsigned char symbol)
{
	if (x < 0 || x >= screen_width_tiles || y < 0 || y >= screen_height_tiles)
	{
		return;
	}
	tiles[x + y*screen_width_tiles] = symbol;
}

void Renderer::drawString(int x, int y, const std::string & str)
{
	for (int i = 0; i < str.size(); i++)
	{
		drawTile(x + i, y, str[i]);
	}
}
