#pragma once

#include "Scene.hpp"

class CredditsScene : public spic::Scene {
public:
	CredditsScene();
	void SetContents();
	void SetCammera();
	static spic::Scene* Start()
	{
		CredditsScene* a = new CredditsScene();
		return a;
	}
};