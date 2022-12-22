#pragma once
#include <ForceDriven.hpp>
#include "RigidBody.hpp"

class SteeringRocket : public spic::ForceDriven {
public:
	SteeringRocket(const std::string& name, const spic::Point& position, const float angle);
	void SetAttributes(const std::string& name, const spic::Point& position, const float angle);
	void SetSteeringBehaviours();
	void SetGroupBehaviours();
public:
	std::shared_ptr<spic::RigidBody> rigidBody;
};