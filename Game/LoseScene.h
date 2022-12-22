#pragma once

#include "Scene.hpp"

class LoseScene : public spic::Scene {
public:
	LoseScene();

	static spic::Scene* Start();
private:
	void SetCamera();
	void SetContents();
};