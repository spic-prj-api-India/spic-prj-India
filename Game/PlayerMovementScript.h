#pragma once
#include "BehaviourScript.hpp"
#include "Input.hpp"
#include <RigidBody.hpp>

class PlayerMovementScript :
	public spic::BehaviourScript {
public:
	PlayerMovementScript();
	PlayerMovementScript(spic::Input::KeyCode left, spic::Input::KeyCode right, spic::Input::KeyCode up);

	virtual void OnStart() override;
	virtual void OnUpdate() override;
	virtual void OnInput() override;

	virtual void OnTriggerEnter2D(const spic::Collider& collider) override;
	virtual void OnTriggerExit2D(const spic::Collider& collider) override;
private:
	spic::Input::KeyCode left;
	spic::Input::KeyCode right;
	spic::Input::KeyCode up;
	bool collided;
};