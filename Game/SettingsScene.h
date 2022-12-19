#pragma once

#include "Scene.hpp"
#include <functional>
#include "DataHandler.hpp"

class SettingsScene : public spic::Scene {
public:
	SettingsScene();
	static spic::Scene* Start();
private:
	void SetCamera();
	void SetContents();
	void AddButton(const std::string& text, std::function<void()> callback, const float offset);
private:
	std::map<std::string, std::string> settings;
};