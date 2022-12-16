#pragma once

#include "Scene.hpp"

class MenuScene : public spic::Scene {
public:
	MenuScene();

	void SetCamera();
	void SetContents();
	void SetMatchMenu();
	void SetInputListeners();

	static spic::Scene* Start()
	{
		MenuScene* a = new MenuScene();
		return a;
	}
};