#pragma once
#include <BehaviourScript.hpp>
#include "Animator.hpp"
#include "Input.hpp"

class CreditsSceneScript :
	public spic::BehaviourScript {
public:
	virtual void OnInput() override;
	spic::Animator* ani;
	bool start = true;
};