#pragma once

#include "Scene.hpp"

class GameScene : public spic::Scene {
public:
	GameScene();
	static spic::Scene* Start()
	{
		GameScene* a = new GameScene();
		return a;
	}
	void SetCamera();
	void SetContents();
};