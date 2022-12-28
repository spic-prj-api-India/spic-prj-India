#pragma once
#include <ForceDriven.hpp>
#include "RigidBody.hpp"

class Alien : public spic::ForceDriven {
public:
	Alien(const std::string& name, const spic::Point& position, const float angle);
	void SetAttributes(const std::string& name, const spic::Point& position, const float angle);
	void SetSteeringBehaviours();
};