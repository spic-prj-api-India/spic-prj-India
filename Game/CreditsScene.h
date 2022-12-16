#pragma once

#include "Scene.hpp"

class CreditsScene : public spic::Scene {
public:
	CreditsScene();
	void SetContents();
	void SetCammera();
	static spic::Scene* Start()
	{
		CredditsScene* a = new CredditsScene();
		return a;
	}
};