#pragma once

#include "Scene.hpp"

class LoseScene : public spic::Scene {
public:
	LoseScene();

	void SetCamera();
	void SetContents();

	static spic::Scene* Start();
};