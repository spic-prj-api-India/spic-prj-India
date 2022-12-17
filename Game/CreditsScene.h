#pragma once

#include "Scene.hpp"

class CreditsScene : public spic::Scene {
public:
	CreditsScene();
	void SetContents();
	void SetCamera();

	static spic::Scene* Start();
};