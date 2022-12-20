#include "CreditsSceneScript.h"

void CreditsSceneScript::OnInput()
{
	if (spic::input::GetKeyDown(spic::input::KeyCode::SPACE))
	{
		if (true)
		{
			this->ani->Play(false);
			this->source->Play(false);

		}
	}
}