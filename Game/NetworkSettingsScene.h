#pragma once

#include "Scene.hpp"
#include <functional>
#include "DataHandler.hpp"
#include <Text.hpp>
#include "InputTypeListener.h"

class NetworkSettingsScene : public spic::Scene {
public:
	NetworkSettingsScene();
	static spic::Scene* Start();
private:
	void SetCamera();
	void SetContents();
	void RestoreSettings();
	void AddButton(const std::string& name, const std::string& text, std::function<void()> callback, const float offset);
private:
	std::map<std::string, std::string> settings;
	std::string ip;
	std::shared_ptr<spic::Text> ipText;
	std::shared_ptr<InputTypeListener> typeListener;
};