#pragma once
#include "BehaviourScript.hpp"
#include <Timer.hpp>
#include "Text.hpp"

class TimerScript :
	public spic::BehaviourScript {
public:
	TimerScript(std::shared_ptr<spic::Text> text);

	virtual void OnStart() override;
	virtual void OnUpdate() override;
	virtual void OnInput() override;
private:
	std::shared_ptr<spic::Text> text;
	std::shared_ptr<spic::Timer> timer;
	int counter;
};