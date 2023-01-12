#include "InstructionsScene.h"
#include "Text.hpp"
#include "Animator.hpp"
#include "BackScript.h"
#include "AudioSource.hpp"
#include <DataHandler.hpp>
#include <Input.hpp>
#include <Button.hpp>
#include <GameEngine.hpp>

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
	AddButton("Jenga game instructions", []() {
		spic::GameEngine::GetInstance()->LoadSceneByName("jenga-instructions");
		}, 0.0f);
	AddButton("Rocket game instructions", []() {
		spic::GameEngine::GetInstance()->LoadSceneByName("rocketgame-instructions");
		}, 100.0f);
	AddButton("Flock/Steering Demo instructions", []() {
		spic::GameEngine::GetInstance()->LoadSceneByName("steering-instructions");
		}, 200.0f);
	AddButton("Key functions", []() {
		spic::GameEngine::GetInstance()->LoadSceneByName("key-functions");
		}, 300.0f);
	AddButton("Back to menu", []() {
		spic::GameEngine::GetInstance()->LoadSceneByName("menu");
		}, 400.0f);
}

void InstructionsScene::AddButton(const std::string& text, std::function<void()> callback, const float offset)
{
	std::shared_ptr<spic::Button> button = std::make_shared<spic::Button>(450.0f, 100.0f, text, spic::Color::white(), "assets/textures/buttons/Button22.png");
	button->Transform(std::make_shared<spic::Transform>(spic::Point(400.0f, 150.0f + offset), 0.0f, 1.0f));
	auto textTransform = button->GetChild<spic::Text>()->Transform();
	textTransform->position.y = 35.0f;
	button->OnClick(callback);
	AddContent(button);
}

spic::Scene* InstructionsScene::Start()
{
	spic::input::UnSubscribeAll();
	InstructionsScene* a = new InstructionsScene();
	return a;
}
