#include "MenuScene.h"
#include <Button.hpp>
#include "GameEngine.hpp"
#include <Text.hpp>
#include "KeyListener.h"
#include <Input.hpp>
#include "FlockingScene.h"
#include "GameScene.h"

MenuScene::MenuScene() : Scene()
{
	SetCamera();
	SetContents();
	SetInputListeners();
}

spic::Scene* MenuScene::Start()
{
	MenuScene* a = new MenuScene();
	return a;
}

void MenuScene::SetCamera()
{
	std::unique_ptr<spic::Camera> camera = std::make_unique<spic::Camera>();
	camera->Transform(std::make_shared<spic::Transform>(spic::Point(0.0f, 0.0f), 0.0f, 1.0f));
	camera->BackgroundColor(spic::Color::magenta());
	camera->BackgroundImage("assets/textures/backgrounds/BG_1.png");
	Camera(std::move(camera));
}

void MenuScene::SetContents()
{
	AddButton("Start Game", []() {
		spic::input::UnSubscribeAll();
		spic::GameEngine::GetInstance()->LoadSceneByName("game");
		}, 0.0f);
	AddButton("Load Game", []() {
		spic::input::UnSubscribeAll();
		std::shared_ptr<GameScene> sceneToLoad = std::make_shared<GameScene>();
		spic::GameEngine::GetInstance()->LoadSceneBySaveFile(sceneToLoad, "game");
		}, 100.0f);
	AddButton("Start Flocking", []() {
		spic::input::UnSubscribeAll();
		spic::GameEngine::GetInstance()->LoadSceneByName("flock");
		}, 200.0f);
	AddButton("Credits", []() {
		spic::input::UnSubscribeAll();
		spic::GameEngine::GetInstance()->LoadSceneByName("credits");
		}, 300.0f);
}

void MenuScene::SetMatchMenu()
{
}

void MenuScene::SetInputListeners()
{
}

void MenuScene::AddButton(const std::string& text, std::function<void()> callback, const float offset)
{
	std::shared_ptr<spic::Button> button = std::make_shared<spic::Button>(200.0f, 100.0f, text, spic::Color::white(), "assets/textures/buttons/Button22.png");
	button->Transform(std::make_shared<spic::Transform>(spic::Point(500.0f, 260.0f+offset), 0.0f, 1.0f));
	auto textTransform = button->GetChild<spic::Text>()->Transform();
	textTransform->position.y = 35.0f;
	button->OnClick(callback);
	AddContent(button);
}