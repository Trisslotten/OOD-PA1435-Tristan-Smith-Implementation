#pragma once

#include <string>

class ITextListener
{
public:
	virtual void updateText(const std::string& text) = 0;
};