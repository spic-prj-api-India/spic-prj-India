#pragma once

#include "Scene.hpp"

class FlockingScene : public spic::Scene {
public:
	FlockingScene();
	static spic::Scene* Start();
	void SetCamera();
	void SetContents();
	void SetListeners();
};