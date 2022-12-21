#pragma once
#include <ForceDriven.hpp>
#include "RigidBody.hpp"

class Rocket : public spic::GameObject {
public:
	Rocket(const std::string& name);
	void SetAttributes();
};