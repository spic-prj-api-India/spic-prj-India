#pragma once

#include "Scene.hpp"

class NetworkScene : public spic::Scene {
public:
	NetworkScene();

	static spic::Scene* Start();
private:
	void SetCamera();
	void SetContents();
};