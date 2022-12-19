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

using namespace spic;

SettingsScene::SettingsScene() : Scene()
{
	SetCamera();
	SetContents();
}

spic::Scene* SettingsScene::Start()
{
	SettingsScene* a = new SettingsScene();
	return a;
}

void SettingsScene::SetCamera()
{
	std::unique_ptr<spic::Camera> camera = std::make_unique<spic::Camera>();
	camera->Transform(std::make_shared<spic::Transform>(spic::Point(0.0f, 0.0f), 0.0f, 1.0f));
	camera->BackgroundColor(spic::Color::magenta());
	camera->BackgroundImage("assets/textures/backgrounds/BG_1.png");
	Camera(std::move(camera));
}

void SettingsScene::SetContents()
{
	auto titleText = std::make_shared<spic::Text>(1200.0f, 900.0f
		, "Settings"
		, ""
		, 50
		, spic::Alignment::CENTER
		, spic::Color::white());

	titleText->Transform(std::make_shared<spic::Transform>(spic::Point(0.0f, 0.0f), 0.0f, 1.0f));
	AddContent(titleText);

	AddButton("restoreSettingsBtn", "Restore settings", [this]() {
		RestoreSettings();

		}, -50.0f);

	AddButton("backgroundMusicButton", "Background music ON", [this]() {
		spic::DataHandler dataHandler = spic::DataHandler("settings");
	dataHandler.LoadSettings(settings);
	settings["background_music"] == "1" ? settings["background_music"] = "0" : settings["background_music"] = "1";
	dataHandler.AddSettings(settings);
	dataHandler.Save();
	std::shared_ptr<spic::GameObject> bgMusicBtn = std::shared_ptr<spic::Button>()->Find("backgroundMusicButton");
	settings["background_music"] == "1" ? bgMusicBtn->GetComponent<Sprite>()->Color(Color::green()) : bgMusicBtn->GetComponent<Sprite>()->Color(Color::white());

		}, 50.0f);

	
}

void SettingsScene::RestoreSettings()
{
	spic::DataHandler dataHandler = spic::DataHandler("settings");
	dataHandler.LoadSettings(settings);
	settings["background_music"] == "1" ? settings["background_music"] = "0" : settings["background_music"] = "1";
	std::shared_ptr<spic::GameObject> bgMusicBtn = std::shared_ptr<spic::Button>()->Find("backgroundMusicButton");
	settings["background_music"] == "1" ? bgMusicBtn->GetComponent<Sprite>()->Color(spic::Color::green()) : bgMusicBtn->GetComponent<Sprite>()->Color(spic::Color::white());
}

void SettingsScene::AddButton(const std::string& name, const std::string& text, std::function<void()> callback, const float offset)
{
	std::shared_ptr<spic::Button> button = std::make_shared<spic::Button>(200.0f, 100.0f, text, spic::Color::white(), "assets/textures/buttons/Button22.png");
	button->Name(name);
	button->Transform(std::make_shared<spic::Transform>(spic::Point(500.0f, 260.0f + offset), 0.0f, 1.0f));
	auto textTransform = button->GetChild<spic::Text>()->Transform();
	textTransform->position.y = 35.0f;
	button->OnClick(callback);
	AddContent(button);
}