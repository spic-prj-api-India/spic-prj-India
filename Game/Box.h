#pragma once
#include <GameObject.hpp>
#include "Persistable.hpp"

class Box : public spic::GameObject, public spic::Persistable
{
public:
	Box();
	Box(const std::string& name, const spic::Point& position);
	void SetAttributes(const spic::Point& position);
};