#pragma once
#include <iostream>
#include <BehaviourScript.hpp>
#include <GameObject.hpp>

class CameraMovementScript :
	public spic::BehaviourScript {
public:
	virtual void OnStart() override;
	virtual void OnUpdate() override;
	virtual void OnTriggerEnter2D(const spic::Collider& collider) override;
	virtual void OnTriggerExit2D(const spic::Collider& collider) override;
	virtual void OnTriggerStay2D(const spic::Collider& collider) override;
};