#pragma once

#include "Scene.hpp"
#include <functional>
#include <Button.hpp>
#include "CheckWinConditionScript.h"

class DifficultyScene : public spic::Scene {
public:
	DifficultyScene();
	static spic::Scene* Start();
private:
	void SetCamera();
	void SetContents();
	void AddButton(const std::string& name, const std::string& text, std::function<void()> callback, const float offset);
private:
	std::map<std::string, std::shared_ptr<spic::Button>> buttons;
};