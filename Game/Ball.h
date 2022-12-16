#pragma once
#include <GameObject.hpp>

class Ball : public spic::GameObject {
public:
	Ball(const std::string& name, const spic::Point& position, const std::string& sprite, const float scale);
	void SetAttributes(const spic::Point& position, const std::string& sprite, const float scale);
};