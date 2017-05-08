#pragma once

#include "textlistener.hpp"
#include "renderer.hpp"

#include <sstream>

class UIElement : public ITextListener
{
	unsigned int x, y;

	std::vector<std::string> lines;

public:

	virtual void updateText(const std::string& text);
	
	void render(Renderer& renderer);

};