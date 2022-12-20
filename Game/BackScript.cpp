#include "BackScript.h"
#include "Input.hpp"
#include <GameEngine.hpp>

void BackScript::OnStart() {
	pressed = false;
}

void BackScript::OnUpdate() {
	if(pressed)
		spic::GameEngine::GetInstance()->LoadSceneByName("menu");
}

void BackScript::OnInput()
{
	if (spic::input::GetKeyDown(spic::input::KeyCode::BACKSPACE) && !pressed)
	{
		pressed = true;
	}
}