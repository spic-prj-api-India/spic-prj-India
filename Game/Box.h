#pragma once
#include <GameObject.hpp>
#include "Persistable.hpp"

class Box : public spic::GameObject, public spic::Persistable
{
public:
	Box();
};