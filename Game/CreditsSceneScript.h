#pragma once
#include <BehaviourScript.hpp>
#include "Animator.hpp"
#include "Input.hpp"
#include <AudioSource.hpp>

class CreditsSceneScript :
	public spic::BehaviourScript {
public:
	virtual void OnInput() override;
	spic::Animator* ani;
	spic::AudioSource* source;
	bool start = true;
};