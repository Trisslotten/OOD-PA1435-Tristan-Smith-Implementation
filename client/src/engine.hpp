#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "playerviewstate.hpp"
#include "world.hpp"
#include "renderer.hpp"
#include "packetparser.hpp"
#include "networking.hpp"

class Engine
{
	Renderer renderer;

	Networking networking;

	PacketParser packet_parser;

	World world;

	std::shared_ptr<PlayerViewState> viewstate;

	std::vector<Item> item;
public:

	World& getWorld();
	Networking& getNetworking();
	const Renderer& getRenderer() const;
	std::shared_ptr<PlayerViewState> getViewState();

	Engine(sf::IpAddress ip, Port port);
	Engine() = delete;

	void windowEvent(sf::Event event);

	void update();

	void receive(sf::Time receive_time);

	void render(sf::RenderTarget& target);


};