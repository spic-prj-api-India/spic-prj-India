#pragma once

#include "Scene.hpp"
#include <functional>

class MenuScene : public spic::Scene {
public:
	MenuScene();
private:
	void SetCamera();
	void SetContents();
	void SetMatchMenu();
	void SetInputListeners();
	void AddButton(const std::string& text, std::function<void()> callback, const float offset);
};