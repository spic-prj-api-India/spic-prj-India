#pragma once

#include "Scene.hpp"
#include <functional>

class MenuScene : public spic::Scene {
public:
	MenuScene();
	static spic::Scene* Start();
private:
	void SetCamera();
	void SetContents();
	void AddButton(const std::string& text, std::function<void()> callback, const float offset);
};