#include "CameraMovementScript.h"
#include "Input.hpp"

void CameraMovementScript::OnStart() {
}
void CameraMovementScript::OnUpdate() {
	if (spic::Input::GetKeyDown(spic::Input::KeyCode::RIGHT_ARROW))
		gameObject->Transform()->position.x = gameObject->Transform()->position.x + 10.0f;
	if (spic::Input::GetKeyDown(spic::Input::KeyCode::LEFT_ARROW))
		gameObject->Transform()->position.x = gameObject->Transform()->position.x - 10.0f;
	if (spic::Input::GetKeyDown(spic::Input::KeyCode::UP_ARROW))
		gameObject->Transform()->position.y = gameObject->Transform()->position.y - 10.0f;
	if (spic::Input::GetKeyDown(spic::Input::KeyCode::DOWN_ARROW))
		gameObject->Transform()->position.y = gameObject->Transform()->position.y + 10.0f;
}
void CameraMovementScript::OnTriggerEnter2D(const spic::Collider& collider) {
}

void CameraMovementScript::OnTriggerExit2D(const spic::Collider& collider) {
}

void CameraMovementScript::OnTriggerStay2D(const spic::Collider& collider) {
}