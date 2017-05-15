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
public:

	World& getWorld();
	Networking& getNetworking();
	const Renderer& getRenderer() const;

	Engine();

	void update();

	void receive(sf::Time receive_time);

	void render(sf::RenderTarget& target);

};