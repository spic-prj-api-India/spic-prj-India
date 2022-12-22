#include "CreditsScene.h"
#include "Text.hpp"
#include "Animator.hpp"
#include "CreditsSceneScript.h"
#include "BackScript.h"
#include "AudioSource.hpp"
#include "Settings.h"
CreditsScene::CreditsScene()
{
	SetCamera();
	SetContents();
}

void CreditsScene::SetCamera()
{
	std::unique_ptr<spic::Camera> camera = std::make_unique<spic::Camera>();
	camera->Transform(std::make_shared<spic::Transform>(spic::Point(0.0f, 0.0f), 0.0f, 1.0f));
	camera->BackgroundColor(spic::Color::green());
	camera->BackgroundImage("assets/textures/backgrounds/392777.png");
	camera->AddComponent<spic::BehaviourScript>(std::make_shared<BackScript>());
	Camera(std::move(camera));
}

void CreditsScene::SetContents()
{
	auto credits = std::make_shared<spic::Text>(1200.0f, 900.0f
		, "Made by:\nCollin Knuit\nBart Blaak\nMilo van der pas\n\n\nPress 'backspace' to return to menu\nPress 'spacebar' for fun"
		, ""
		, 50
		, spic::Alignment::CENTER
		, spic::Color::white());


	if (background_music)
	{
		auto music = std::make_shared<spic::AudioSource>("assets/music/1-03 Strepitoso Fight.mp3", true, true, 0.2f);
		credits->AddComponent(music);
	}

	credits->Transform(std::make_shared<spic::Transform>(spic::Point(0.0f, 0.0f), 0.0f, 1.0f));
	

	auto animatorObject1 = std::make_shared<spic::GameObject>();
	animatorObject1->Transform(std::make_shared<spic::Transform>(spic::Point(0.0f, 200.0f), 0.0f, 0.5f));
	auto animator1 = std::make_shared<spic::Animator>(10);
	animator1->InitHorizontalSpriteSheet("assets/textures/animated-explosion/Explosion_9/spritesheet.png", 10, 800, 800);
	animator1->Stop();

	auto script1 = std::make_shared<CreditsSceneScript>();

	auto music1 = std::make_shared<spic::AudioSource>("assets/music/mi_explosion_03_hpx.mp3", false, false, 1.0f);
	script1->ani = animator1.get();
	script1->source = music1.get();
	animatorObject1->AddComponent(std::move(music1));
	animatorObject1->AddComponent(std::move(animator1));
	animatorObject1->AddComponent(std::move(script1));
	credits->AddChild(std::move(animatorObject1));

	this->AddContent(credits);
}

spic::Scene* CreditsScene::Start()
{
	spic::input::UnSubscribeAll();
	CreditsScene* a = new CreditsScene();
	return a;
}
