#pragma once

#include "Scene.hpp"

class InstructionsScene : public spic::Scene {
public:
	InstructionsScene();

	static spic::Scene* Start();
private:
	void SetContents();
	void SetCamera();
};