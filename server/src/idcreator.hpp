#pragma once

#include "../../shared/definitions.hpp"

class IDCreator
{
	ID counter = 0;
public:

	inline ID newID()
	{
		ID new_id = counter;
		counter++;
		return new_id;
	}
};