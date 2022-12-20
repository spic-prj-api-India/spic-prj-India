#pragma once
#include <BehaviourScript.hpp>

class BoxSpawnerScript :
	public spic::BehaviourScript {
public:
	virtual void OnStart() override;
	virtual void OnUpdate() override;
	virtual void OnInput() override;
private:
	bool leftPressed;
	bool rightPressed;
};