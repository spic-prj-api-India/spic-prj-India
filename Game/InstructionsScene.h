#pragma once

#include "Scene.hpp"
#include <functional>

class InstructionsScene : public spic::Scene {
public:
	InstructionsScene();

	static spic::Scene* Start();
private:
	void SetContents();
	void SetCamera();
	void AddButton(const std::string& text, std::function<void()> callback, const float offset);
};