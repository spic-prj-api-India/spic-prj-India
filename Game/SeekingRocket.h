#pragma once
#include <ForceDriven.hpp>
#include "RigidBody.hpp"

class SeekingRocket : public spic::ForceDriven {
public:
	SeekingRocket(const std::string& name, const spic::Point& position, const float angle);
	void SetAttributes(const std::string& name, const spic::Point& position, const float angle);
	void SetSteeringBehaviours();
	void SetGroupBehaviours();
public:
	std::shared_ptr<spic::RigidBody> rigidBody;
};