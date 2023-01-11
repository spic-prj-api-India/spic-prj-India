#include "InstructionsScene.h"
#include "Text.hpp"
#include "Animator.hpp"
#include "BackScript.h"
#include "AudioSource.hpp"
#include <DataHandler.hpp>
#include <Input.hpp>

InstructionsScene::InstructionsScene()
{
	SetCamera();
	SetContents();
}

void InstructionsScene::SetCamera()
{
	std::unique_ptr<spic::Camera> camera = std::make_unique<spic::Camera>();
	camera->Transform(std::make_shared<spic::Transform>(spic::Point(0.0f, 0.0f), 0.0f, 1.0f));
	camera->BackgroundColor(spic::Color::green());
	camera->BackgroundImage("assets/textures/backgrounds/392777.png");
	camera->AddComponent<spic::BehaviourScript>(std::make_shared<BackScript>());
	Camera(std::move(camera));
}

void InstructionsScene::SetContents()
{
	auto instructions = std::make_shared<spic::Text>(
		1200.0f // width
		, 900.0f // height
		, "Jenga game instructions:\n"
		, "" // font
		, 25 // size
		, spic::Alignment::CENTER // alignment
		, spic::Color::white()); // color
	
	auto shortcuts = std::make_shared<spic::Text>(
		1200.0f // width
		, 900.0f // height
		, "Keyboard shortcuts\n"
		, "" // font
		, 25 // size
		, spic::Alignment::CENTER // alignment
		, spic::Color::white()); // color
	
	AddContent(instructions);
}

spic::Scene* InstructionsScene::Start()
{
	spic::input::UnSubscribeAll();
	InstructionsScene* a = new InstructionsScene();
	return a;
}
