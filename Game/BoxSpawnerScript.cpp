#include "BoxSpawnerScript.h"
#include "Input.hpp"
#include <GameEngine.hpp>
#include "BoxPersistable.h"
#include "BoxNotPersistable.h"
#include "GeneralHelper.hpp"
#include <RandomHelper.hpp>

using namespace spic;
using namespace spic::input;
using namespace spic::helper_functions;

BoxSpawnerScript::BoxSpawnerScript()
{
	leftPressed = false;
	rightPressed = false;
	switcher = true;
	timer = std::make_shared<spic::Timer>();
}

void BoxSpawnerScript::OnStart() {
	int delay = RandomHelper::GetInstance()->Between<int>(2000, 5000);
	timer->Start(std::chrono::milliseconds(delay), [this]() mutable {
		switcher = !switcher;
		});
}

void BoxSpawnerScript::OnUpdate() {
	if ((rightPressed && switcher) || (leftPressed && !switcher))
	{
		spic::Point mousePosition = MousePosition();
		mousePosition += this->Parent()->Transform()->position;
		mousePosition -= 25.0f;
		std::shared_ptr<BoxPersistable> boxPresistable = std::make_shared<BoxPersistable>("box-" + general_helper::GetRandomUUID(), mousePosition);
		spic::GameObject::Create(boxPresistable);
		this->bloopAudio->Play(false);
		if (switcher)
			rightPressed = false;
		else
			leftPressed = false;
	}
	if ((leftPressed && switcher) || (rightPressed && !switcher))
	{
		spic::Point mousePosition = MousePosition();
		mousePosition += this->Parent()->Transform()->position;
		mousePosition -= 25.0f;
		std::shared_ptr<BoxNotPersistable> boxNotPresistable = std::make_shared<BoxNotPersistable>("box-" + general_helper::GetRandomUUID(), mousePosition);
		spic::GameObject::Create(boxNotPresistable);
		this->bloopAudio->Play(false);
		if (switcher)
			leftPressed = false;
		else
			rightPressed = false;
	}
}

void BoxSpawnerScript::OnInput()
{
	if (spic::input::GetMouseButtonDown(spic::input::MouseButton::LEFT) && !leftPressed)
	{
		leftPressed = true;
	}
	else if (spic::input::GetMouseButtonDown(spic::input::MouseButton::RIGHT) && !rightPressed)
	{
		rightPressed = true;
	}
}