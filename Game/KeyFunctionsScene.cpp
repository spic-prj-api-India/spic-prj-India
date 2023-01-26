#include "KeyFunctionsScene.h"
#include "Text.hpp"
#include "Animator.hpp"
#include "BackScript.h"
#include "AudioSource.hpp"
#include <DataHandler.hpp>
#include <Input.hpp>
#include <GameEngine.hpp>
#include <Button.hpp>

KeyFunctionsScene::KeyFunctionsScene()
{
	SetCamera();
	SetContents();
}

void KeyFunctionsScene::SetCamera()
{
	std::unique_ptr<spic::Camera> camera = std::make_unique<spic::Camera>();
	camera->Transform(std::make_shared<spic::Transform>(spic::Point(0.0f, 0.0f), 0.0f, 1.0f));
	camera->BackgroundColor(spic::Color::green());
	camera->BackgroundImage("assets/textures/backgrounds/392777.png");
	camera->AddComponent<spic::BehaviourScript>(std::make_shared<BackScript>());
	Camera(std::move(camera));
}

void KeyFunctionsScene::SetContents()
{
	auto instructions = std::make_shared<spic::Text>(
		1200.0f // width
		, 900.0f // height
		, "Backspace: return to menu\nF1: Toggle FPS counter\nLeft / Right arrows : move camera left / right(when applicable)\nPage up / down : Increase / decrease gameplay speed(when applicable)\nLeft mouse button : Shoot rocket"
		, "" // font
		, 25 // size
		, spic::Alignment::CENTER
		, spic::Color::white());
	instructions->Transform(std::make_shared<spic::Transform>(spic::Point(10.0f, 200.0f), 0.0f, 1.0f));
	
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

spic::Scene* KeyFunctionsScene::Start()
{
	spic::input::UnSubscribeAll();
	KeyFunctionsScene* a = new KeyFunctionsScene();
	return a;
}
