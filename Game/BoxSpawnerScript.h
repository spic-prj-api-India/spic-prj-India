#pragma once
#include <BehaviourScript.hpp>
#include <AudioSource.hpp>

class BoxSpawnerScript :
	public spic::BehaviourScript {
public:
	virtual void OnStart() override;
	virtual void OnUpdate() override;
	virtual void OnInput() override;
	spic::AudioSource* bloopAudio;

private:
	bool leftPressed;
	bool rightPressed;

};