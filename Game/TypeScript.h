#pragma once
#include <BehaviourScript.hpp>
#include "Text.hpp"

class TypeScript :
	public spic::BehaviourScript {
public:
	TypeScript(std::shared_ptr<spic::Text> text, std::string& opponentIp);
	virtual void OnStart() override;
	virtual void OnUpdate() override;
	virtual void OnInput() override;
private:
	bool pressed;
};