#include "PlayerMovementScript.h"

PlayerMovementScript::PlayerMovementScript() 
	: PlayerMovementScript(spic::Input::KeyCode::A, spic::Input::KeyCode::D, spic::Input::KeyCode::W)
{}

PlayerMovementScript::PlayerMovementScript(spic::Input::KeyCode left, spic::Input::KeyCode right, spic::Input::KeyCode up)
	: left{left}, right{right}, up{up}
{}

void PlayerMovementScript::OnStart() {
	collided = false;
}

void PlayerMovementScript::OnUpdate() {
}

void PlayerMovementScript::OnInput() {
	const auto& rigidBody = this->gameObject->GetComponent<spic::RigidBody>();
	if (spic::Input::GetKeyDown(left))
	{
		std::cout << "Pressed left" << std::endl;
		rigidBody->AddForce({ -1.0f, 0.0f });
	}
	if (spic::Input::GetKeyDown(right))
	{
		std::cout << "Pressed right" << std::endl;
		rigidBody->AddForce({ 1.0f, 0.0f });
	}
	if (spic::Input::GetKeyDown(up) && collided == true)
	{
		collided = false;
		std::cout << "Pressed up" << std::endl;
		rigidBody->AddForce({ 0.0f, -3.0f });
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