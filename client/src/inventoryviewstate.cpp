#include "inventoryviewstate.hpp"
#include "engine.hpp"
#include <iostream>
#include "input.hpp"
#include "engine.hpp"

void InventoryViewState::init(Engine& engine)
{
	engine.getNetworking().sendRequestInventory();
	engine.getNetworking().sendRequestEquipped();
}

void InventoryViewState::windowEvent(sf::Event event, Engine& engine)
{}

std::shared_ptr<PlayerViewState> InventoryViewState::update(Engine & engine)
{
	sf::Vector2i vel;
	if (key::pressed(sf::Keyboard::I))
	{
		//exit inventory
		return std::make_shared<PlayingViewState>();
	}
	if (key::pressed(sf::Keyboard::E))
	{
		//equip item
		engine.getNetworking().sendEquipItem(engine.getWorld().getLatestInventory()[currentItem + page * 30].getItemId());
	}
	if (key::pressed(sf::Keyboard::D)) //temporary drop item thing, drops item with global id 0 aka. The Crazy Thing
	{
		engine.getNetworking().sendDropItem(engine.getWorld().getLatestInventory()[currentItem + page * 30].getItemId());
		return std::make_shared<PlayingViewState>();
	}
	if (key::down(sf::Keyboard::Up))
	{
		if (currentItem - 1 >= 0)
			currentItem = currentItem - 1;
	}
	if (key::down(sf::Keyboard::Down))
	{
		if (currentItem + page * 30 + 1 < engine.getWorld().getLatestInventory().size() && currentItem +1 <30)
		{
			currentItem = currentItem + 1;
		}
	}
	if (key::pressed(sf::Keyboard::Left))
	{
		if (page - 1 >= 0)
		{
			currentItem = 0;
			page--;
		}
			
	}
	if (key::pressed(sf::Keyboard::Right))
	{
		if ((page + 1) * 30 < engine.getWorld().getLatestInventory().size())
		{
			currentItem = 0;
			page++;
		}
	}

	return nullptr;
}

InventoryViewState::~InventoryViewState()
{}

void InventoryViewState::render(World& world, Renderer& renderer)
{
	sf::Vector2i size = renderer.getScreenSizeTiles();

	std::vector<Item> inv = world.getLatestInventory();
	int maxpages = (inv.size() / 30)+1;
	std::string title = "INVENTORY (PAGE " + std::to_string(page+1) + "/" + std::to_string(maxpages) + ")";
	renderer.drawString(1, 1, title, sf::Color(255,255,255,255));
	for (int i = page*30; i < inv.size() && i < 30*page+30; i++)
	{
		sf::Color color = inv[i].getColor();
		if (i == currentItem+page*30)
			color = sf::Color(0, 255, 200, 200);
		renderer.drawString(1, (i%30)+2, inv[i].getName(), color);
	}
	renderer.drawString(40, 1, "Description", sf::Color(255, 255, 255, 255));
	if(inv.size() > 0)
		renderer.drawString(40, 2, inv[currentItem + page * 30].getDescription(), sf::Color(150, 150, 150, 255));
	renderer.drawString(1, size.y - 4, "[UP/DOWN] Select item, [LEFT/RIGHT] Select page", sf::Color(150, 150, 150, 255));
	renderer.drawString(1, size.y - 3, "[D] Drop, [E] Equip, [I] Exit inventory", sf::Color(150, 150, 150, 255));
	renderer.drawString(40, 30, "Equipped weapon: ");
	if (world.getLatestEquipped() != ID_NOT_FOUND)
	{
		Item equipped = world.getInventoryItemByID(world.getLatestEquipped());
		renderer.drawString(40, 31, equipped.getName(), equipped.getColor());
	}
	
}
