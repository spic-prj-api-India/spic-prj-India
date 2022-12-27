#include "TimerScript.h"
#include "GameEngine.hpp"

TimerScript::TimerScript(std::shared_ptr<spic::Text> text)
{
	this->text = std::move(text);
	timer = std::make_shared<spic::Timer>();
	counter = 20;
}

void TimerScript::OnStart() {
	timer->Start(std::chrono::milliseconds(1000), [this]() mutable {
		counter--;
		});
}

void LoadSaveScene()
{
	spic::GameEngine::GetInstance()->SaveScene("jenga");
	spic::GameEngine::GetInstance()->LoadSceneBySaveFile("jenga-save", "jenga");
}

void TimerScript::OnUpdate() {
	if (counter == 0)
		return LoadSaveScene();
	this->text->_Text(std::to_string(counter));
}

void TimerScript::OnInput()
{

}