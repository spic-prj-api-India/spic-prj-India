#include "CreditsScene.h"
#include "Text.hpp"
#include "Animator.hpp"
#include "CreditsSceneScript.h"
#include "BackScript.h"

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

	credits->Transform(std::make_shared<spic::Transform>(spic::Point(0.0f, 0.0f), 0.0f, 1.0f));


	auto animatorObject1 = std::make_shared<spic::GameObject>();
	animatorObject1->Transform(std::make_shared<spic::Transform>(spic::Point(0.0f, 200.0f), 0.0f, 0.5f));
	auto animator1 = std::make_shared<spic::Animator>(10);
	animator1->InitHorizontalSpriteSheet("assets/textures/animated-explosion/Explosion_9/spritesheet.png", 10, 800, 800);
	animator1->Stop();

	auto script1 = std::make_shared<CreditsSceneScript>();
	script1->ani = animator1.get();
	animatorObject1->AddComponent(std::move(animator1));
	animatorObject1->AddComponent(std::move(script1));


	credits->AddChild(std::move(animatorObject1));

	auto animatorObject2 = std::make_shared<spic::GameObject>();
	animatorObject2->Transform(std::make_shared<spic::Transform>(spic::Point(700.0f, 200.0f), 0.0f, 0.5f));
	auto animator2 = std::make_shared<spic::Animator>(20);
	animator2->InitHorizontalSpriteSheet("assets/textures/animated-explosion/Explosion_9/spritesheet.png", 10, 800, 800);
	animator2->Stop();

	auto script2 = std::make_shared<CreditsSceneScript>();
	script2->ani = animator2.get();

	animatorObject2->AddComponent(std::move(animator2));
	animatorObject2->AddComponent(std::move(script2));
	credits->AddChild(std::move(animatorObject2));

	this->AddContent(credits);
}

spic::Scene* CreditsScene::Start()
{
	CreditsScene* a = new CreditsScene();
	return a;
}
