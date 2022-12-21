#pragma once

#include "Scene.hpp"

class WinScene : public spic::Scene {
public:
	WinScene();

	void SetCamera();
	void SetContents();

	static spic::Scene* Start();
};