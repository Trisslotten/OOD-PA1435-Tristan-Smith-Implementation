#include "uielement.h"

void UIElement::updateText(const std::string & text)
{
	lines.clear();
	std::stringstream sstream(text);
	std::string line;
	while (std::getline(sstream, line, '\n'))
	{
		lines.push_back(line);
	}
}

void UIElement::render(Renderer & renderer)
{
	for (int i = 0; i < lines.size(); i++)
	{
		renderer.drawString(x, y + i, lines[i]);
	}
}
