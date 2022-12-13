#pragma once

#include "Scene.hpp"

class MenuScene : public spic::Scene {
public:
	MenuScene();

	void SetCamera();
	void SetContents();
	void SetMatchMenu();
	void SetInputListeners();
};