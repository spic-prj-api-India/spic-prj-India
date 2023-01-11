#pragma once

#include "Scene.hpp"

class RocketGameInstructionsScene : public spic::Scene {
public:
	RocketGameInstructionsScene();

	static spic::Scene* Start();
private:
	void SetContents();
	void SetCamera();
};