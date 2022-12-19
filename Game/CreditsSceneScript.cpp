#include "CreditsSceneScript.h"

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
}