#include "CredditsSceneScript.h"
#include "GameEngine.hpp"

void CredditsSceneScript::OnInput()
{
	if (spic::Input::GetKeyDown(spic::Input::KeyCode::SPACE))
	{
		if (start)
		{
			this->ani->Play(false);
			start = false;
		}
		else
		{
			this->ani->Stop();
			start = true;
		}
	}

	if (spic::Input::GetKeyDown(spic::Input::KeyCode::BACKSPACE))
	{
		spic::GameEngine::GetInstance()->LoadSceneByName("menu");
	}
}