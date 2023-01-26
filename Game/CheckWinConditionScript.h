#pragma once
#include <BehaviourScript.hpp>
#include <Timer.hpp>
#include <Text.hpp>

enum class WinCondition{
	EASY = 400,
	NORMAL = 250,
	HARD = 100
};

class CheckWinConditionScript :
	public spic::BehaviourScript {
public:
	CheckWinConditionScript(WinCondition difficulty, std::shared_ptr<spic::Text> text);
	virtual void OnStart() override;
	virtual void OnUpdate() override;
	virtual void OnInput() override;

	void Check();
private:
	WinCondition difficulty;
	std::shared_ptr<spic::Text> text;
	std::shared_ptr<spic::Timer> timer;
	int counter;
};