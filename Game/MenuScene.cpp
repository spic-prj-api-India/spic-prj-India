#include "MenuScene.h"
#include <Button.hpp>

MenuScene::MenuScene() : Scene()
{
	SetCamera();
	SetContents();
	LoadTileMap("assets/maps/menu.tmx", 3);
}

void MenuScene::SetCamera()
{
	std::unique_ptr<spic::Camera> camera = std::make_unique<spic::Camera>();
	camera->Transform(std::make_shared<spic::Transform>(spic::Point(0.0f, 0.0f), 0.0f, 1.0f));
	camera->BackgroundColor(spic::Color::white());
	Camera(std::move(camera));
}

void MenuScene::SetContents()
{
	std::shared_ptr<spic::Button> button = std::make_shared<spic::Button>(200.0f, 100.0f, "Start Game");
	button->Transform(std::make_shared<spic::Transform>(spic::Point(600.0f, 400.0f), 0.0f, 1.0f));
	button->OnClick([]() {
		std::cout << "Button clicked" << std::endl;
		});
	AddContent(button);
}