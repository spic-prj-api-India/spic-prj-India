#include "CameraMovementScript.h"
#include "Input.hpp"

void CameraMovementScript::OnStart() {
}
void CameraMovementScript::OnUpdate() {
}

void CameraMovementScript::OnInput() {
	auto transform = gameObject->Transform();

	if (spic::input::GetKeyDown(spic::input::KeyCode::RIGHT_ARROW)
		&& (transform->position.x + 10.0f) <= 2000.0f)
		gameObject->Transform()->position.x = transform->position.x + 10.0f;
	if (spic::input::GetKeyDown(spic::input::KeyCode::LEFT_ARROW) 
		&& (transform->position.x - 10.0f) >= 0.0f)
		transform->position.x = transform->position.x - 10.0f;

	if (spic::input::GetKeyDown(spic::input::KeyCode::UP_ARROW))
		transform->position.y = transform->position.y - 10.0f;
	if (spic::input::GetKeyDown(spic::input::KeyCode::DOWN_ARROW) 
		&& (transform->position.y + 10.0f) <= 0.0f)
		transform->position.y = transform->position.y + 10.0f;
}