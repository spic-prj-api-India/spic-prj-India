#pragma once
#include <BehaviourScript.hpp>
#include <Timer.hpp>
#include <Text.hpp>

enum class WinCondition{
	EASY = 1000,
	NORMAL = 750,
	HARD = 500
};

class CheckWinConditionScript :
	public spic::BehaviourScript {
public:
	CheckWinConditionScript(std::shared_ptr<spic::Text> text);
	virtual void OnStart() override;
	virtual void OnUpdate() override;
	virtual void OnInput() override;

private:
	std::shared_ptr<spic::Text> text;
	std::shared_ptr<spic::Timer> timer;
	int counter;
};