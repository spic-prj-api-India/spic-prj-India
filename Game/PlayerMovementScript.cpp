#include "PlayerMovementScript.h"

void PlayerMovementScript::OnStart() {
	collided = false;
}

void PlayerMovementScript::OnUpdate() {
}

void PlayerMovementScript::OnInput() {
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

void PlayerMovementScript::OnTriggerEnter2D(const spic::Collider& collider)
{
	collided = true;
}

void PlayerMovementScript::OnTriggerExit2D(const spic::Collider& collider)
{
	collided = false;
}