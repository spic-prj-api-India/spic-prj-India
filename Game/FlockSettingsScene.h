#pragma once

#include "Scene.hpp"
#include <functional>
#include "DataHandler.hpp"
#include <Button.hpp>

class FlockSettingsScene : public spic::Scene {
public:
	FlockSettingsScene();
	static spic::Scene* Start();
private:
	void SetCamera();
	void SetContents();
	void RestoreSettings();
	void AddButton(const std::string& name, const std::string& text, std::function<void()> callback, const float offset);
	void AddSettingButton(const std::string& name, const std::string& text, std::function<void()> callback, const float offset);
private:
	std::map<std::string, std::string> settings;
	std::map<std::string, std::shared_ptr<spic::Button>> settingButtons;
};