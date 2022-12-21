#pragma once

#include "Scene.hpp"

class FlockingScene : public spic::Scene {
public:
	FlockingScene();

	void SetCamera();
	void SetContents();

	static spic::Scene* Start();
};