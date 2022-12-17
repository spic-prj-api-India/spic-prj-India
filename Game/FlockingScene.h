#pragma once

#include "Scene.hpp"

class FlockingScene : public spic::Scene {
public:
	FlockingScene();

	static spic::Scene* Start()
	{
		FlockingScene* a = new FlockingScene();
		return a;
	}

	void SetCamera();
	void SetContents();
};