#include "BoxSpawnerScript.h"
#include "Input.hpp"
#include <GameEngine.hpp>
#include "BoxPersistable.h"
#include "BoxNotPersistable.h"
#include "GeneralHelper.hpp"

using namespace spic;
using namespace spic::input;
using namespace spic::helper_functions::general_helper;

void BoxSpawnerScript::OnStart() {
	leftPressed = false;
	rightPressed = false;
}

void BoxSpawnerScript::OnUpdate() {
	if (rightPressed)
	{
		spic::Point mousePosition = MousePosition();
		std::shared_ptr<BoxPersistable> boxPresistable = std::make_shared<BoxPersistable>("box-" + GetRandomUUID(), mousePosition);
		spic::GameObject::Create(boxPresistable);
		this->bloopAudio->Play(false);
		rightPressed = false;
	}
	else if (leftPressed)
	{
		spic::Point mousePosition = MousePosition();
		std::shared_ptr<BoxNotPersistable> boxNotPresistable = std::make_shared<BoxNotPersistable>("box-" + GetRandomUUID(), mousePosition);
		spic::GameObject::Create(boxNotPresistable);
		this->bloopAudio->Play(false);
		leftPressed = false;
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