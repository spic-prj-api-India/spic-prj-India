#pragma once
#include "BehaviourScript.hpp"
#include "Input.hpp"
#include <RigidBody.hpp>

class PlayerMovementScript :
	public spic::BehaviourScript {
public:
	virtual void OnStart() override {
		collided = false;
	}

	virtual void OnUpdate() override {
		const auto& rigidBody = this->gameObject->GetComponent<spic::RigidBody>();
		if (spic::Input::GetKeyDown(spic::Input::KeyCode::A))
		{
			std::cout << "Pressed left" << std::endl;
			rigidBody->AddForce({ -20.0f, 0.0f });
		}
		if (spic::Input::GetKeyDown(spic::Input::KeyCode::D))
		{
			std::cout << "Pressed right" << std::endl;
			rigidBody->AddForce({ 20.0f, 0.0f });
		}
		if (spic::Input::GetKeyDown(spic::Input::KeyCode::W) && collided == true)
		{
			collided = false;
			std::cout << "Pressed up" << std::endl;
			rigidBody->AddForce({ 0.0f, -120.0f });
		}
	}

	virtual void OnTriggerEnter2D(const spic::Collider& collider) override
	{
		collided = true;
	}

	virtual void OnTriggerExit2D(const spic::Collider& collider) override
	{
		collided = false;
	}
private:
	bool collided;
};