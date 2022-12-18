#include "CreditsSceneScript.h"
#include "GameEngine.hpp"

void CreditsSceneScript::OnInput()
{
	if (spic::input::GetKeyDown(spic::input::KeyCode::SPACE))
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

	if (spic::input::GetKeyDown(spic::input::KeyCode::BACKSPACE))
	{
		spic::GameEngine::GetInstance()->LoadSceneByName("menu");
	}
}