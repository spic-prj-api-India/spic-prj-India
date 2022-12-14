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
		spic::Input::UnSubscribeAll();
		spic::GameEngine::GetInstance()->LoadScene(std::make_shared<GameScene>());
		}, 0.0f);
	AddButton("Start Flocking", []() {
		spic::Input::UnSubscribeAll();
		spic::GameEngine::GetInstance()->LoadScene(std::make_shared<FlockingScene>());
		}, 100.0f);
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
	button->Transform(std::make_shared<spic::Transform>(spic::Point(500.0f, 350.0f+offset), 0.0f, 1.0f));
	auto textTransform = button->GetChild<spic::Text>()->Transform();
	textTransform->position.y = 10.0f;
	button->OnClick(callback);
	AddContent(button);
}