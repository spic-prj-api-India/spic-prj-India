#pragma once

#include "Scene.hpp"

class SaveScene : public spic::Scene {
public:
	SaveScene();

	static spic::Scene* Start();
private:
	void SetCamera();
	void SetContents();
};