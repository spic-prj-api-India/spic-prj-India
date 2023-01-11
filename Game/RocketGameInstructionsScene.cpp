#include "RocketGameInstructionsScene.h"
#include "Text.hpp"
#include "Animator.hpp"
#include "BackScript.h"
#include "AudioSource.hpp"
#include <DataHandler.hpp>
#include <Input.hpp>
#include <GameEngine.hpp>
#include <Button.hpp>

RocketGameInstructionsScene::RocketGameInstructionsScene()
{
	SetCamera();
	SetContents();
}

void RocketGameInstructionsScene::SetCamera()
{
	std::unique_ptr<spic::Camera> camera = std::make_unique<spic::Camera>();
	camera->Transform(std::make_shared<spic::Transform>(spic::Point(0.0f, 0.0f), 0.0f, 1.0f));
	camera->BackgroundColor(spic::Color::green());
	camera->BackgroundImage("assets/textures/backgrounds/392777.png");
	camera->AddComponent<spic::BehaviourScript>(std::make_shared<BackScript>());
	Camera(std::move(camera));
}

void RocketGameInstructionsScene::SetContents()
{
	auto instructions = std::make_shared<spic::Text>(
		1100.0f // width
		, 900.0f // height
		, "Rocket game instructions:\n\n\There are two players. Player one controls the rocket launcher. Player two acts as the mouse cursor. \nAs player one, your objective is to shoot a maximum of five rockets, which will try to \nfollow and hit player two.\nYou lose the game when more than five rockets have been launched without hitting player two.\nYou win when one rocket hits player two.\n\nAs player two, your objective is to survive for as long as possible by avoiding player one's rockets\n until they have  used all of their rockets without hitting you.\nYou win when player two has fired all of their five rockets without hitting you.\n\nThe IP address of your opponent can be set in the settings screen."
		, "" // font
		, 25 // size
		, spic::Alignment::CENTER
		, spic::Color::white());
	instructions->Transform(std::make_shared<spic::Transform>(spic::Point(50.0f, 20.0f), 0.0f, 1.0f));

	auto button = std::make_shared<spic::Button>(
		250.0f // width
		, 100.0f // height
		, "Return"
		, spic::Color::white()
		, "assets/textures/buttons/Button22.png");
	button->Name("return-button");
	button->Transform(std::make_shared<spic::Transform>(spic::Point(500.0f, 550.0f), 0.0f, 1.0f));
	auto textTransform = button->GetChild<spic::Text>()->Transform();
	textTransform->position.y = 35.0f;
	button->OnClick([]() {
		spic::GameEngine::GetInstance()->LoadSceneByName("instructions");
		});

	AddContent(button);
	AddContent(instructions);
}

spic::Scene* RocketGameInstructionsScene::Start()
{
	spic::input::UnSubscribeAll();
	RocketGameInstructionsScene* a = new RocketGameInstructionsScene();
	return a;
}
