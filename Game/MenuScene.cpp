#include "MenuScene.h"
#include <Button.hpp>
#include "GameEngine.hpp"
#include <Text.hpp>
#include "KeyListener.h"
#include <Input.hpp>
#include "GameScene.h"

MenuScene::MenuScene() : Scene()
{
	SetCamera();
	SetContents();
}

void MenuScene::SetCamera()
{
	std::unique_ptr<spic::Camera> camera = std::make_unique<spic::Camera>();
	camera->Transform(std::make_shared<spic::Transform>(spic::Point(0.0f, 0.0f), 0.0f, 1.0f));
	camera->BackgroundColor(spic::Color::magenta());
	camera->BackgroundImage("assets/textures/backgrounds/bg2.png");
	Camera(std::move(camera));
}

void MenuScene::SetContents()
{
	AddButton("Jenga game", []() {
		spic::GameEngine::GetInstance()->LoadSceneByName("jenga-settings");
		}, 0.0f);
	AddButton("Rocket game", []() {
		spic::GameEngine::GetInstance()->LoadSceneByName("network");
		}, 100.0f);
	AddButton("Flock/Steering Demo", []() {
		spic::GameEngine::GetInstance()->LoadSceneByName("steering");
		}, 200.0f);
	AddButton("Credits", []() {
		spic::GameEngine::GetInstance()->LoadSceneByName("credits");
		}, 300.0f);
	AddButton("Settings", []() {
		spic::GameEngine::GetInstance()->LoadSceneByName("settings");
		}, 400.0f);	
	AddButton("Instructions", []() {
		spic::GameEngine::GetInstance()->LoadSceneByName("instructions");
		}, 500.0f);
}

void MenuScene::AddButton(const std::string& text, std::function<void()> callback, const float offset)
{
	std::shared_ptr<spic::Button> button = std::make_shared<spic::Button>(300.0f, 100.0f, text, spic::Color::white(), "assets/textures/buttons/Button22.png");
	button->Transform(std::make_shared<spic::Transform>(spic::Point(500.0f, 150.0f+offset), 0.0f, 1.0f));
	auto textTransform = button->GetChild<spic::Text>()->Transform();
	textTransform->position.y = 35.0f;
	button->OnClick(callback);
	AddContent(button);
}

spic::Scene* MenuScene::Start()
{
	spic::input::UnSubscribeAll();
	MenuScene* a = new MenuScene();
	return a;
}