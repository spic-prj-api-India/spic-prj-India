#pragma once

#include "Scene.hpp"

class CreditsScene : public spic::Scene {
public:
	CreditsScene();

	static spic::Scene* Start();
private:
	void SetContents();
	void SetCamera();
};