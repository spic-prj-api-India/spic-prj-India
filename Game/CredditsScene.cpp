#include "CredditsScene.h"
#include "Text.hpp"
#include "Animator.hpp"
#include "CredditsSceneScript.h"

CredditsScene::CredditsScene()
{
	SetCammera();
	SetContents();
}

void CredditsScene::SetContents()
{
	auto creddits = std::make_shared<spic::Text>(1200, 900
		, "Made by:\nCollin Knuit\nBart Blaak\nMilo van der pas\n\n\nPress 'backspace' to return to menu\n\n\nPress 'spacebar' for fun"
		, ""
		, 50
		, spic::Alignment::CENTER
		, spic::Color::white());

	creddits->Transform(std::make_shared<spic::Transform>(spic::Point(0.0f, 0.0f), 0.0f, 1.0f));


	auto animatorObject1 = std::make_shared<spic::GameObject>();
	animatorObject1->Transform(std::make_shared<spic::Transform>(spic::Point(0.0f, 200.0f), 0.0f, 0.5f));
	auto animator1 = std::make_shared<spic::Animator>(10);
	animator1->InitHorizontalSpriteSheet("assets/textures/animated-explosion/Explosion_9/spritesheet.png",10, 800, 800);
	animator1->Stop();

	auto script1 = std::make_shared<CredditsSceneScript>();
	script1->ani = animator1.get();
	animatorObject1->AddComponent(std::move(animator1));

	animatorObject1->AddComponent(std::move(script1));

	
	creddits->AddChild(std::move(animatorObject1));

	auto animatorObject2 = std::make_shared<spic::GameObject>();
	animatorObject2->Transform(std::make_shared<spic::Transform>(spic::Point(700.0f, 200.0f), 0.0f, 0.5f));
	auto animator2 = std::make_shared<spic::Animator>(20);
	animator2->InitHorizontalSpriteSheet("assets/textures/animated-explosion/Explosion_9/spritesheet.png", 10, 800, 800);
	animator2->Stop();

	auto script2 = std::make_shared<CredditsSceneScript>();
	script2->ani = animator2.get();

	animatorObject2->AddComponent(std::move(animator2));
	animatorObject2->AddComponent(std::move(script2));
	creddits->AddChild(std::move(animatorObject2));

	this->AddContent(creddits);
}

void CredditsScene::SetCammera()
{
	std::unique_ptr<spic::Camera> camera = std::make_unique<spic::Camera>();
	camera->Transform(std::make_shared<spic::Transform>(spic::Point(0.0f, 0.0f), 0.0f, 1.0f));
	camera->BackgroundColor(spic::Color::green());
	camera->BackgroundImage("assets/textures/backgrounds/392777.png");
	Camera(std::move(camera));
}
