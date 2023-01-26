#include "FlockSettingsScene.h"
#include <Button.hpp>
#include "GameEngine.hpp"
#include <Text.hpp>
#include "KeyListener.h"
#include <Input.hpp>
#include "GameScene.h"
#include "DataHandler.hpp"
#include "Text.hpp"

using namespace spic;

FlockSettingsScene::FlockSettingsScene() : Scene()
{
	SetCamera();
	SetContents();
	RestoreSettings();
}

void FlockSettingsScene::SetCamera()
{
	std::unique_ptr<spic::Camera> camera = std::make_unique<spic::Camera>();
	camera->Transform(std::make_shared<spic::Transform>(spic::Point(0.0f, 0.0f), 0.0f, 1.0f));
	camera->BackgroundColor(spic::Color::magenta());
	camera->BackgroundImage("assets/textures/backgrounds/bg2.png");
	Camera(std::move(camera));
}

void FlockSettingsScene::SetContents()
{
	auto titleText = std::make_shared<spic::Text>(1250.0f, 900.0f
		, "Flock/Steering settings"
		, ""
		, 50
		, spic::Alignment::CENTER
		, spic::Color::white());

	titleText->Transform(std::make_shared<spic::Transform>(spic::Point(0.0f, 100.0f), 0.0f, 1.0f));
	AddContent(titleText);

	AddButton("menuBtn", "Back to settings", [this]() {
		GameEngine::GetInstance()->LoadSceneByName("settings");
		}, -50.0f);

	AddSettingButton("use_wander", "Use wander", [this]() {
		spic::DataHandler dataHandler = spic::DataHandler("flock_settings");
		settings["use_wander"] == "1" ? settings["use_wander"] = "0" : settings["use_wander"] = "1";
		dataHandler.AddSettings(settings);
		dataHandler.Save();

		settings["use_wander"] == "1" ?
			settingButtons["use_wander"]->GetComponent<Sprite>()->Color(Color::green()) :
			settingButtons["use_wander"]->GetComponent<Sprite>()->Color(Color::white());
		}, 40.0f);
	AddSettingButton("use_seek", "Use seek", [this]() {
		spic::DataHandler dataHandler = spic::DataHandler("flock_settings");
		settings["use_seek"] == "1" ? settings["use_seek"] = "0" : settings["use_seek"] = "1";
		dataHandler.AddSettings(settings);
		dataHandler.Save();

		settings["use_seek"] == "1" ?
			settingButtons["use_seek"]->GetComponent<Sprite>()->Color(Color::green()) :
			settingButtons["use_seek"]->GetComponent<Sprite>()->Color(Color::white());
		}, 130.0f);
	AddSettingButton("use_flee", "Use flee", [this]() {
		spic::DataHandler dataHandler = spic::DataHandler("flock_settings");
		settings["use_flee"] == "1" ? settings["use_flee"] = "0" : settings["use_flee"] = "1";
		dataHandler.AddSettings(settings);
		dataHandler.Save();

		settings["use_flee"] == "1" ?
			settingButtons["use_flee"]->GetComponent<Sprite>()->Color(Color::green()) :
			settingButtons["use_flee"]->GetComponent<Sprite>()->Color(Color::white());
		}, 220.0f);
	AddSettingButton("use_arrival", "Use arrival", [this]() {
		spic::DataHandler dataHandler = spic::DataHandler("flock_settings");
		settings["use_arrival"] == "1" ? settings["use_arrival"] = "0" : settings["use_arrival"] = "1";
		dataHandler.AddSettings(settings);
		dataHandler.Save();

		settings["use_arrival"] == "1" ?
			settingButtons["use_arrival"]->GetComponent<Sprite>()->Color(Color::green()) :
			settingButtons["use_arrival"]->GetComponent<Sprite>()->Color(Color::white());
		}, 310.0f);
}

void FlockSettingsScene::RestoreSettings()
{
	spic::DataHandler dataHandler = spic::DataHandler("flock_settings");
	dataHandler.LoadSettings(settings);
	settings["use_wander"] == "0" ?
		settingButtons["use_wander"]->GetComponent<Sprite>()->Color(spic::Color::white()) :
		settingButtons["use_wander"]->GetComponent<Sprite>()->Color(spic::Color::green());
	settings["use_seek"] == "0" ?
		settingButtons["use_seek"]->GetComponent<Sprite>()->Color(spic::Color::white()) :
		settingButtons["use_seek"]->GetComponent<Sprite>()->Color(spic::Color::green());
	settings["use_flee"] == "0" ?
		settingButtons["use_flee"]->GetComponent<Sprite>()->Color(spic::Color::white()) :
		settingButtons["use_flee"]->GetComponent<Sprite>()->Color(spic::Color::green());
	settings["use_arrival"] == "0" ?
		settingButtons["use_arrival"]->GetComponent<Sprite>()->Color(spic::Color::white()) :
		settingButtons["use_arrival"]->GetComponent<Sprite>()->Color(spic::Color::green());
}

void FlockSettingsScene::AddButton(const std::string& name, const std::string& text, std::function<void()> callback, const float offset)
{
	auto button = std::make_shared<spic::Button>(250.0f, 100.0f, text, spic::Color::white(), "assets/textures/buttons/Button22.png");
	button->Name(name);
	button->Transform(std::make_shared<spic::Transform>(spic::Point(500.0f, 260.0f + offset), 0.0f, 1.0f));
	auto textTransform = button->GetChild<spic::Text>()->Transform();
	textTransform->position.y = 35.0f;
	button->OnClick(callback);
	AddContent(button);
}

void FlockSettingsScene::AddSettingButton(const std::string& name, const std::string& text, std::function<void()> callback, const float offset)
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

spic::Scene* FlockSettingsScene::Start()
{
	spic::input::UnSubscribeAll();
	FlockSettingsScene* a = new FlockSettingsScene();
	return a;
}