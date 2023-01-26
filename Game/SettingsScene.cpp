#include "MenuScene.h"
#include <Button.hpp>
#include "GameEngine.hpp"
#include <Text.hpp>
#include "KeyListener.h"
#include <Input.hpp>
#include "GameScene.h"
#include "SettingsScene.h"
#include "DataHandler.hpp"
#include "Text.hpp"

using namespace spic;

SettingsScene::SettingsScene() : Scene()
{
	SetCamera();
	SetContents();
}

void SettingsScene::SetCamera()
{
	std::unique_ptr<spic::Camera> camera = std::make_unique<spic::Camera>();
	camera->Transform(std::make_shared<spic::Transform>(spic::Point(0.0f, 0.0f), 0.0f, 1.0f));
	camera->BackgroundColor(spic::Color::magenta());
	camera->BackgroundImage("assets/textures/backgrounds/bg2.png");
	Camera(std::move(camera));
}

void SettingsScene::SetContents()
{
	auto titleText = std::make_shared<spic::Text>(1250.0f, 900.0f
		, "Settings"
		, ""
		, 50
		, spic::Alignment::CENTER
		, spic::Color::white());

	titleText->Transform(std::make_shared<spic::Transform>(spic::Point(0.0f, 100.0f), 0.0f, 1.0f));
	AddContent(titleText);

	AddButton("menuBtn", "Back to Menu", [this]() {
		GameEngine::GetInstance()->LoadSceneByName("menu");
		}, -50.0f);

	AddButton("soundBtn", "Sound", []() {
		spic::GameEngine::GetInstance()->LoadSceneByName("soundSettings");
		}, 40.0f);

	AddButton("networkBtn", "Networking", []() {
		spic::GameEngine::GetInstance()->LoadSceneByName("networkSettings");
		}, 130.0f);

	AddButton("flockBtn", "Flocking/steering", []() {
		spic::GameEngine::GetInstance()->LoadSceneByName("flockSettings");
		}, 220.0f);
}

void SettingsScene::AddButton(const std::string& name, const std::string& text, std::function<void()> callback, const float offset)
{
	auto button = std::make_shared<spic::Button>(250.0f, 100.0f, text, spic::Color::white(), "assets/textures/buttons/Button22.png");
	button->Name(name);
	button->Transform(std::make_shared<spic::Transform>(spic::Point(500.0f, 260.0f + offset), 0.0f, 1.0f));
	auto textTransform = button->GetChild<spic::Text>()->Transform();
	textTransform->position.y = 35.0f;
	button->OnClick(callback);
	AddContent(button);
}

spic::Scene* SettingsScene::Start()
{
	spic::input::UnSubscribeAll();
	SettingsScene* a = new SettingsScene();
	return a;
}