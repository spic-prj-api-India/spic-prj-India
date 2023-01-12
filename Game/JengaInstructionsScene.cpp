#include "JengaInstructionsScene.h"
#include "Text.hpp"
#include "Animator.hpp"
#include "BackScript.h"
#include "AudioSource.hpp"
#include <DataHandler.hpp>
#include <Input.hpp>
#include <GameEngine.hpp>
#include <Button.hpp>

JengaInstructionsScene::JengaInstructionsScene()
{
	SetCamera();
	SetContents();
}

void JengaInstructionsScene::SetCamera()
{
	std::unique_ptr<spic::Camera> camera = std::make_unique<spic::Camera>();
	camera->Transform(std::make_shared<spic::Transform>(spic::Point(0.0f, 0.0f), 0.0f, 1.0f));
	camera->BackgroundColor(spic::Color::green());
	camera->BackgroundImage("assets/textures/backgrounds/392777.png");
	camera->AddComponent<spic::BehaviourScript>(std::make_shared<BackScript>());
	Camera(std::move(camera));
}

void JengaInstructionsScene::SetContents()
{
	auto instructions = std::make_shared<spic::Text>(
		1200.0f // width
		, 900.0f // height
		, "Jenga game instructions:\n\n\nIn this game, the objective of the player is to \nbuild a tower of boxes that should \nreach a certain height (visualised with a red line) \nto win the game.\n\nThe two buttons can be pressed to spawn persistable and non-persistable boxes.\nEvery 2-5 seconds, the mouse buttons switch functions.\nThe non-persistable boxes are removed every 20 seconds.\nThe higher the chosen difficulty, the greater the height of the red line."
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

spic::Scene* JengaInstructionsScene::Start()
{
	spic::input::UnSubscribeAll();
	JengaInstructionsScene* a = new JengaInstructionsScene();
	return a;
}
