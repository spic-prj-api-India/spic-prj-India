#pragma once
#include <GameObject.hpp>
#include "Persistable.hpp"

class Box : public spic::Persistable
{
public:
	Box() : Persistable()
	{
		Name("Box");
	}

	void Load() override
	{

	}

	void Save() override
	{

	}
};