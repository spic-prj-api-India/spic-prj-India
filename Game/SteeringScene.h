#pragma once

#include "Scene.hpp"

class SteeringScene : public spic::Scene {
public:
	SteeringScene();

	static spic::Scene* Start();
private:
	void SetCamera(bool mapSwitch);
	void SetContents();
	bool mapSwitch;
};