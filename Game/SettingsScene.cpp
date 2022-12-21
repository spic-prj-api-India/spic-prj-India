#include "MenuScene.h"
#include <Button.hpp>
#include "GameEngine.hpp"
#include <Text.hpp>
#include "KeyListener.h"
#include <Input.hpp>
#include "FlockingScene.h"
#include "GameScene.h"
#include "SettingsScene.h"
#include "DataHandler.hpp"
#include "Text.hpp"
#include "BackScript.h"

using namespace spic;

SettingsScene::SettingsScene() : Scene()
{
	SetCamera();
	SetContents();
	RestoreSettings();
}

void SettingsScene::SetCamera()
{
	std::unique_ptr<spic::Camera> camera = std::make_unique<spic::Camera>();
	camera->Transform(std::make_shared<spic::Transform>(spic::Point(0.0f, 0.0f), 0.0f, 1.0f));
	camera->BackgroundColor(spic::Color::magenta());
	camera->BackgroundImage("assets/textures/backgrounds/bg2.png");
	camera->AddComponent<spic::BehaviourScript>(std::make_shared<BackScript>());
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

	AddSettingButton("background_music", "Background music", [this]() {
		spic::DataHandler dataHandler = spic::DataHandler("settings");
		settings["background_music"] == "1" ? settings["background_music"] = "0" : settings["background_music"] = "1";
		dataHandler.AddSettings(settings);
		dataHandler.Save();
		settings["background_music"] == "1" ? 
			settingButtons["background_music"]->GetComponent<Sprite>()->Color(Color::green()) :
			settingButtons["background_music"]->GetComponent<Sprite>()->Color(Color::white());
		}, 50.0f);
}

void SettingsScene::RestoreSettings()
{
	spic::DataHandler dataHandler = spic::DataHandler("settings");
	dataHandler.LoadSettings(settings);
	settings["background_music"] == "0" ? 
		settingButtons["background_music"]->GetComponent<Sprite>()->Color(spic::Color::white()) : 
		settingButtons["background_music"]->GetComponent<Sprite>()->Color(spic::Color::green());
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

void SettingsScene::AddSettingButton(const std::string& name, const std::string& text, std::function<void()> callback, const float offset)
{
	auto button = std::make_shared<spic::Button>(250.0f, 100.0f, text, spic::Color::white(), "assets/textures/buttons/Button22.png");
	button->Name(name);
	button->Transform(std::make_shared<spic::Transform>(spic::Point(500.0f, 260.0f + offset), 0.0f, 1.0f));
	auto textTransform = button->GetChild<spic::Text>()->Transform();
	textTransform->position.y = 35.0f;
	button->OnClick(callback);
	AddContent(button);
	settingButtons[name] = button;
}

spic::Scene* SettingsScene::Start()
{
	spic::input::ResetSubscribedEvents();
	SettingsScene* a = new SettingsScene();
	return a;
}