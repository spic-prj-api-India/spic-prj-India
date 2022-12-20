#pragma once

#include "Scene.hpp"

class FlockingScene : public spic::Scene {
public:
	FlockingScene();
	static spic::Scene* Start();
	void RestoreSettings();
	void SetCamera();

	void SetContentsPlayer1();
	void SetContentsPlayer2();
private:
	std::map<std::string, std::string> settings;
};