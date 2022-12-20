#include "BoxSpawnerScript.h"
#include "Input.hpp"
#include <GameEngine.hpp>
#include "BoxPersistable.h"
#include "BoxNotPersistable.h"

using namespace spic;
using namespace spic::input;

void BoxSpawnerScript::OnStart() {
	leftPressed = false;
	rightPressed = false;
}

void BoxSpawnerScript::OnUpdate() {
	if (rightPressed)
	{
		boxCount++;
		spic::Point mousePosition = MousePosition();
		std::shared_ptr<BoxPersistable> boxPresistable = std::make_shared<BoxPersistable>("box" + std::to_string(boxCount), mousePosition);
		spic::GameObject::Create(boxPresistable);
		rightPressed = false;
	}
	else if (leftPressed)
	{
		boxCount++;
		spic::Point mousePosition = MousePosition();
		std::shared_ptr<BoxNotPersistable> boxNotPresistable = std::make_shared<BoxNotPersistable>("box" + std::to_string(boxCount), mousePosition);
		spic::GameObject::Create(boxNotPresistable);
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