#pragma once

#include "Scene.hpp"

class JengaInstructionsScene : public spic::Scene {
public:
	JengaInstructionsScene();

	static spic::Scene* Start();
private:
	void SetContents();
	void SetCamera();
};