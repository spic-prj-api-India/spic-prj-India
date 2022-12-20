#pragma once

#include "Obstacle.hpp"
#include <GameObject.hpp>

class CircleObstacle : public spic::GameObject, public spic::Obstacle {
public:
	CircleObstacle(const std::string& name, const spic::Point& position);
	void SetAttributes(const spic::Point& position);
};