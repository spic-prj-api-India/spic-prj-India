#pragma once
#include <GameObject.hpp>

class Player : public spic::GameObject
{
public:
	Player();
	Player(const spic::Point& position, const bool isShooter = true);
	void SetAttributes(const spic::Point& position);
	void SetContent(std::map<std::string, std::string>& data) override;

	bool IsShooter() const;
private:
	bool isShooter;
};