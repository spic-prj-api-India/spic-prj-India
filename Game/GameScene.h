#pragma once

#include "Scene.hpp"

class GameScene : public spic::Scene {
public:
	GameScene();
	static spic::Scene* Start();
	void SetCamera();
	void SetContents();
};