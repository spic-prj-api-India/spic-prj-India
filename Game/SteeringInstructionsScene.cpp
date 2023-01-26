#include "SteeringInstructionsScene.h"
#include "Text.hpp"
#include "Animator.hpp"
#include "BackScript.h"
#include "AudioSource.hpp"
#include <DataHandler.hpp>
#include <Input.hpp>
#include <GameEngine.hpp>
#include <Button.hpp>

SteeringInstructionsScene::SteeringInstructionsScene()
{
	SetCamera();
	SetContents();
}

void SteeringInstructionsScene::SetCamera()
{
	std::unique_ptr<spic::Camera> camera = std::make_unique<spic::Camera>();
	camera->Transform(std::make_shared<spic::Transform>(spic::Point(0.0f, 0.0f), 0.0f, 1.0f));
	camera->BackgroundColor(spic::Color::green());
	camera->BackgroundImage("assets/textures/backgrounds/392777.png");
	camera->AddComponent<spic::BehaviourScript>(std::make_shared<BackScript>());
	Camera(std::move(camera));
}

void SteeringInstructionsScene::SetContents()
{
	auto instructions = std::make_shared<spic::Text>(
		1200.0f // width
		, 900.0f // height
		, "Steering/Flocking demo instructions:\n\n\In this demo, you can experience the AI capabilities of the engine.\nPress the left mouse button to shoot as many rockets as you want.\nThe rockets will behave accordingly to how you \nconfigured the settings for wander/seek/flee/arrival behavior.\n\nA random amount of aliens spawn in the map. \nIf a rocket collides with an alien, the rocket will disappear.\n\nOne of two different maps will be loaded, based on a random calculated choice."
		, "" // font
		, 25 // size
		, spic::Alignment::CENTER
		, spic::Color::white());

	auto button = std::make_shared<spic::Button>(
		250.0f // width
		, 100.0f // height
		, "Return"
		, spic::Color::white()
		, "assets/textures/buttons/Button22.png");
	button->Name("return-button");
	button->Transform(std::make_shared<spic::Transform>(spic::Point(500.0f, 450.0f), 0.0f, 1.0f));
	auto textTransform = button->GetChild<spic::Text>()->Transform();
	textTransform->position.y = 35.0f;
	button->OnClick([]() {
		spic::GameEngine::GetInstance()->LoadSceneByName("instructions");
		});

	AddContent(button);
	AddContent(instructions);
}

spic::Scene* SteeringInstructionsScene::Start()
{
	spic::input::UnSubscribeAll();
	SteeringInstructionsScene* a = new SteeringInstructionsScene();
	return a;
}
