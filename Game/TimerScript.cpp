#include "TimerScript.h"

TimerScript::TimerScript(std::shared_ptr<spic::Text> text)
{
	this->text = std::move(text);
	timer = std::make_shared<spic::Timer>();
	counter = 0;
}

void TimerScript::OnStart() {
	timer->Start(std::chrono::milliseconds(1000), [this]() mutable {
		counter++;
		});
}

void TimerScript::OnUpdate() {
	this->text->_Text(std::to_string(counter));
}

void TimerScript::OnInput()
{

}