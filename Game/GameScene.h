#pragma once

#include "Scene.hpp"

class GameScene : public spic::Scene {
public:
	GameScene();

	static spic::Scene* Start();
private:
	void SetCamera();
	void SetContents();
};