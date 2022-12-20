#pragma once
#include <BehaviourScript.hpp>

class BackScript :
	public spic::BehaviourScript {
public:
	virtual void OnStart() override;
	virtual void OnUpdate() override;
	virtual void OnInput() override;
private:
	bool pressed;
};