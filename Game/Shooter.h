#pragma once
#include <GameObject.hpp>

class Shooter : public spic::GameObject
{
public:
	Shooter();
	Shooter(const spic::Point& position);
	void SetAttributes(const spic::Point& position);
	void SetContent(std::map<std::string, std::string>& data) override;

	void Init();
};