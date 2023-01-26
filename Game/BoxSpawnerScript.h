#pragma once
#include <BehaviourScript.hpp>
#include <AudioSource.hpp>
#include <Timer.hpp>

class BoxSpawnerScript :
	public spic::BehaviourScript {
public:
	BoxSpawnerScript();
	virtual void OnStart() override;
	virtual void OnUpdate() override;
	virtual void OnInput() override;
	spic::AudioSource* bloopAudio;

private:
	std::shared_ptr<spic::Timer> timer;
	bool switcher;
	bool leftPressed;
	bool rightPressed;
};