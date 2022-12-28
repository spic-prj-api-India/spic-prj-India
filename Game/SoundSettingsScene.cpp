#include "SoundSettingsScene.h"
#include <Button.hpp>
#include "GameEngine.hpp"
#include <Text.hpp>
#include "KeyListener.h"
#include <Input.hpp>
#include "GameScene.h"
#include "DataHandler.hpp"
#include "Text.hpp"

using namespace spic;

SoundSettingsScene::SoundSettingsScene() : Scene()
{
	SetCamera();
	SetContents();
	RestoreSettings();
}

void SoundSettingsScene::SetCamera()
{
	std::unique_ptr<spic::Camera> camera = std::make_unique<spic::Camera>();
	camera->Transform(std::make_shared<spic::Transform>(spic::Point(0.0f, 0.0f), 0.0f, 1.0f));
	camera->BackgroundColor(spic::Color::magenta());
	camera->BackgroundImage("assets/textures/backgrounds/bg2.png");
	Camera(std::move(camera));
}

void SoundSettingsScene::SetContents()
{
	auto titleText = std::make_shared<spic::Text>(1250.0f, 900.0f
		, "Sound settings"
		, ""
		, 50
		, spic::Alignment::CENTER
		, spic::Color::white());

	titleText->Transform(std::make_shared<spic::Transform>(spic::Point(0.0f, 100.0f), 0.0f, 1.0f));
	AddContent(titleText);

	AddButton("menuBtn", "Back to settings", [this]() {
		GameEngine::GetInstance()->LoadSceneByName("settings");
		}, -50.0f);

	AddSettingButton("background_music", "Background music", [this]() {
		spic::DataHandler dataHandler = spic::DataHandler("sound_settings");
		settings["background_music"] == "1" ? settings["background_music"] = "0" : settings["background_music"] = "1";
		dataHandler.AddSettings(settings);
		dataHandler.Save();

		settings["background_music"] == "1" ?
			settingButtons["background_music"]->GetComponent<Sprite>()->Color(Color::green()) :
			settingButtons["background_music"]->GetComponent<Sprite>()->Color(Color::white());
		}, 40.0f);
}

void SoundSettingsScene::RestoreSettings()
{
	spic::DataHandler dataHandler = spic::DataHandler("sound_settings");
	dataHandler.LoadSettings(settings);
	settings["background_music"] == "0" ?
		settingButtons["background_music"]->GetComponent<Sprite>()->Color(spic::Color::white()) :
		settingButtons["background_music"]->GetComponent<Sprite>()->Color(spic::Color::green());
}

void SoundSettingsScene::AddButton(const std::string& name, const std::string& text, std::function<void()> callback, const float offset)
{
	auto button = std::make_shared<spic::Button>(250.0f, 100.0f, text, spic::Color::white(), "assets/textures/buttons/Button22.png");
	button->Name(name);
	button->Transform(std::make_shared<spic::Transform>(spic::Point(500.0f, 260.0f + offset), 0.0f, 1.0f));
	auto textTransform = button->GetChild<spic::Text>()->Transform();
	textTransform->position.y = 35.0f;
	button->OnClick(callback);
	AddContent(button);
}

void SoundSettingsScene::AddSettingButton(const std::string& name, const std::string& text, std::function<void()> callback, const float offset)
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

spic::Scene* SoundSettingsScene::Start()
{
	spic::input::UnSubscribeAll();
	SoundSettingsScene* a = new SoundSettingsScene();
	return a;
}