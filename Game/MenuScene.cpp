#include "MenuScene.h"
#include <Button.hpp>
#include "GameEngine.hpp"
#include <Text.hpp>
#include "MouseListener.h"
#include "KeyListener.h"
#include <Input.hpp>

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
	{
		std::shared_ptr<spic::Button> button = std::make_shared<spic::Button>(200.0f, 100.0f, "Start Game", spic::Color::white(), "assets/textures/buttons/Button22.png");
		button->Transform(std::make_shared<spic::Transform>(spic::Point(500.0f, 350.0f), 0.0f, 1.0f));
		auto textTransform = button->GetChild<spic::Text>()->Transform();
		textTransform->position.y = 35.0f;
		button->OnClick([]() {
			spic::Input::UnSubscribeAll();
			spic::GameEngine::GetInstance()->LoadSceneByName("game");
			});
		AddContent(button);
	}
	
	{
		std::shared_ptr<spic::Button> button2 = std::make_shared<spic::Button>(200.0f, 100.0f, "Creddits", spic::Color::white(), "assets/textures/buttons/Button22.png");
		button2->Transform(std::make_shared<spic::Transform>(spic::Point(500.0f, 450.0f), 0.0f, 1.0f));
		auto textTransform2 = button2->GetChild<spic::Text>()->Transform();
		textTransform2->position.y = 35.0f;
		button2->OnClick([]() {
			spic::Input::UnSubscribeAll();
			spic::GameEngine::GetInstance()->LoadSceneByName("creddits");
			});
		AddContent(button2);
	}

	
	
}

void MenuScene::SetMatchMenu()
{
}

void MenuScene::SetInputListeners()
{
	std::shared_ptr<MouseListener> mouseListener = std::make_shared<MouseListener>();
	std::shared_ptr<KeyListener> keyListener = std::make_shared<KeyListener>();
	spic::Input::Subscribe(spic::Input::MouseButton::LEFT, mouseListener);
	spic::Input::Subscribe(spic::Input::KeyCode::A, keyListener);
}