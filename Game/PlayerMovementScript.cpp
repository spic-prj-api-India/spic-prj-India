#include "PlayerMovementScript.h"

PlayerMovementScript::PlayerMovementScript() 
	: PlayerMovementScript(spic::input::KeyCode::A, spic::input::KeyCode::D, spic::input::KeyCode::W)
{}

PlayerMovementScript::PlayerMovementScript(spic::input::KeyCode left, spic::input::KeyCode right, spic::input::KeyCode up)
	: left{left}, right{right}, up{up}
{}

void PlayerMovementScript::OnStart() {
	collided = false;
}

void PlayerMovementScript::OnUpdate() {
}

void PlayerMovementScript::OnInput() {
	const auto& rigidBody = this->Parent()->GetComponent<spic::RigidBody>();
	if (spic::input::GetKeyDown(left))
	{
		std::cout << "Pressed left" << std::endl;
		rigidBody->AddForce({ -1.0f, 0.0f });
	}
	if (spic::input::GetKeyDown(right))
	{
		std::cout << "Pressed right" << std::endl;
		rigidBody->AddForce({ 1.0f, 0.0f });
	}
	if (spic::input::GetKeyDown(up) && collided == true)
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