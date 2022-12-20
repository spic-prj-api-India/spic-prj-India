#pragma once
#include <iostream>
#include <BehaviourScript.hpp>
#include <GameObject.hpp>

class CameraMovementScript :
	public spic::BehaviourScript {
public:
	virtual void OnStart() override;
	virtual void OnUpdate() override;
	virtual void OnInput() override;
};