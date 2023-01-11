#include "CheckWinConditionScript.h"
#include "Input.hpp"
#include <GameEngine.hpp>
#include "BoxPersistable.h"
#include "BoxNotPersistable.h"
#include "GeneralHelper.hpp"
#include <RandomHelper.hpp>

using namespace spic;
using namespace spic::helper_functions;

CheckWinConditionScript::CheckWinConditionScript(WinCondition difficulty, std::shared_ptr<spic::Text> text) : difficulty{ difficulty }
{
	this->text = std::move(text);
	timer = std::make_shared<spic::Timer>();
	counter = 10;
}

void CheckWinConditionScript::OnStart() {
	timer->Start(std::chrono::milliseconds(1000), [this]() mutable {
		counter--;
		});
}

void CheckWinConditionScript::OnUpdate() {
	if (counter == 0)
		return Check();
	this->text->_Text(std::to_string(counter));
}

void CheckWinConditionScript::OnInput()
{
}

void CheckWinConditionScript::Check()
{
	auto boxes = spic::GameObject::FindObjectsOfType<BoxPersistable>();
	for (const auto& box : boxes) {
		if (static_cast<int>(difficulty) < box->Transform()->position.y)
			continue;

		spic::GameEngine::GetInstance()->LoadSceneByName("won");
		return;
	}
	spic::GameEngine::GetInstance()->LoadSceneByName("lost");
}