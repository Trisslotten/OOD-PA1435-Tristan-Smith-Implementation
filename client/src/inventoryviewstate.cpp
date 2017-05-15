#include "inventoryviewstate.hpp"
#include "engine.hpp"
#include <iostream>

#include "engine.hpp"

void InventoryViewState::init(Engine& engine)
{
	engine.getNetworking().sendRequestInventory();
}

std::shared_ptr<PlayerViewState> InventoryViewState::update(Engine & engine)
{
	PlayerViewState* returnstate = nullptr;
	sf::Vector2i vel;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
	{
		//exit inventory
		PlayingViewState* playstate = new PlayingViewState();
		returnstate = playstate;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) //temporary drop item thing, drops item with global id 0 aka. The Crazy Thing
	{
		PlayingViewState* playstate = new PlayingViewState();
		returnstate = playstate;
		engine.getNetworking().sendDropItem(engine.getWorld().getLatestInventory()[currentItem + page * 30].getItemId());
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (currentItem - 1 >= 0)
			currentItem = currentItem - 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (currentItem + page * 30 + 1 < engine.getWorld().getLatestInventory().size() && currentItem +1 <30)
		{
			currentItem = currentItem + 1;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (page - 1 >= 0)
		{
			currentItem = 0;
			page--;
		}
			
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if ((page + 1) * 30 < engine.getWorld().getLatestInventory().size())
		{
			currentItem = 0;
			page++;
		}
	}

	return (std::shared_ptr<PlayerViewState>)returnstate;
}

InventoryViewState::~InventoryViewState()
{}

void InventoryViewState::render(World& world, Renderer& renderer)
{
	std::vector<Item> inv = world.getLatestInventory();
	int maxpages = (inv.size() / 30)+1;
	std::string title = "INVENTORY (PAGE " + std::to_string(page+1) + "/" + std::to_string(maxpages) + ")";
	renderer.drawString(1, 1, title, sf::Color(255,255,255,255));
	for (int i = page*30; i < inv.size() && i < 30*page+30; i++)
	{
		sf::Color color = sf::Color(230, 230, 230, 230);
		if (i == currentItem+page*30)
			color = sf::Color(0, 255, 200, 200);
		renderer.drawString(1, (i%30)+2, inv[i].getName(), color);
	}
	renderer.drawString(40, 1, "Description", sf::Color(255, 255, 255, 255));
	if(inv.size() > 0)
		renderer.drawString(40, 2, inv[currentItem + page * 30].getDescription(), sf::Color(150, 150, 150, 255));
	renderer.drawString(1, 40, "UP/DOWN item select, LEFT/RIGHT page select. 30 items per page.", sf::Color(150, 150, 150, 255));
	renderer.drawString(1, 41, "Press D to drop item, E to equip.", sf::Color(150, 150, 150, 255));
}
