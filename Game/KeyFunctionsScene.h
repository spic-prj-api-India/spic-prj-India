#pragma once

#include "Scene.hpp"

class KeyFunctionsScene : public spic::Scene {
public:
	KeyFunctionsScene();

	static spic::Scene* Start();
private:
	void SetContents();
	void SetCamera();
};