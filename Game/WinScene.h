#pragma once

#include "Scene.hpp"

class WinScene : public spic::Scene {
public:
	WinScene();

	static spic::Scene* Start();
private:
	void SetCamera();
	void SetContents();
};