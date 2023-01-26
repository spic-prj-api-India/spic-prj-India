#pragma once

#include "Scene.hpp"

class SteeringInstructionsScene : public spic::Scene {
public:
	SteeringInstructionsScene();

	static spic::Scene* Start();
private:
	void SetContents();
	void SetCamera();
};