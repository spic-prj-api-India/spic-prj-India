#pragma once
#include <GameObject.hpp>

class Target : public spic::GameObject
{
public:
	Target();
	Target(const spic::Point& position);
	void SetAttributes(const spic::Point& position);
	void SetContent(std::map<std::string, std::string>& data) override;

	void SetListener();
};