#pragma once

#include "Scene.hpp"

class FlockingScene : public spic::Scene {
public:
	FlockingScene();

	static spic::Scene* Start();
private:
	void SetCamera();
	void SetContents();
};