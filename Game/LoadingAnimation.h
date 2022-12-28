#pragma once
#include <GameObject.hpp>

class LoadingAnimation : public spic::GameObject
{
public:
	LoadingAnimation(const std::string& name, const spic::Point& position, const std::string& loadingText, const bool active = true);
	void SetAttributes(const spic::Point& position, const std::string& loadingText, const bool active);
};