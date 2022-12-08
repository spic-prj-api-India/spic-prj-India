#pragma once

#include "Scene.hpp"

class GameScene : public spic::Scene {
public:
	GameScene();

	void SetCamera();
	void SetContents();
};