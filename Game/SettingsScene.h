#pragma once

#include "Scene.hpp"
#include <functional>
#include "DataHandler.hpp"
#include <Button.hpp>

class SettingsScene : public spic::Scene {
public:
	SettingsScene();
	static spic::Scene* Start();
private:
	void SetCamera();
	void SetContents();
	void AddButton(const std::string& name, const std::string& text, std::function<void()> callback, const float offset);
};