#include "NetworkBackScript.h"
#include "Input.hpp"
#include <GameEngine.hpp>
#include "SyncScript.h"

void NetworkBackScript::OnStart() {
	pressed = false;
}

void NetworkBackScript::OnUpdate() {
	if (pressed) {
		this->Parent()->GetComponent<SyncScript>()->NotifyExit();
		spic::GameEngine::GetInstance()->LoadSceneByName("menu");
	}
}

void NetworkBackScript::OnInput()
{
	if (spic::input::GetKeyDown(spic::input::KeyCode::BACKSPACE) && !pressed)
	{
		pressed = true;
	}
}