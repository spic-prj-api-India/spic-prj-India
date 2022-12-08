#pragma once
#include <Flock.hpp>
#include "RigidBody.hpp"

class Rocket : public spic::Flock {
public:
	Rocket(const std::string& name, const spic::Point& position, const float angle);
	void SetAttributes(const std::string& name, const spic::Point& position, const float angle);
	void SetWeights();
public:
	std::shared_ptr<spic::RigidBody> rigidBody;
};