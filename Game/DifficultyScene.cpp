#include "DifficultyScene.h"
#include <Button.hpp>
#include "GameEngine.hpp"
#include <Text.hpp>
#include "KeyListener.h"
#include <Input.hpp>
#include "GameScene.h"
#include "DataHandler.hpp"
#include "Text.hpp"

using namespace spic;

DifficultyScene::DifficultyScene() : Scene()
{
	SetCamera();
	SetContents();
}

void DifficultyScene::SetCamera()
{
	std::unique_ptr<spic::Camera> camera = std::make_unique<spic::Camera>();
	camera->Transform(std::make_shared<spic::Transform>(spic::Point(0.0f, 0.0f), 0.0f, 1.0f));
	camera->BackgroundColor(spic::Color::magenta());
	camera->BackgroundImage("assets/textures/backgrounds/bg2.png");
	Camera(std::move(camera));
}

void DifficultyScene::SetContents()
{
	auto titleText = std::make_shared<spic::Text>(1250.0f, 900.0f
		, "Difficulty"
		, ""
		, 50
		, spic::Alignment::CENTER
		, spic::Color::white());

	titleText->Transform(std::make_shared<spic::Transform>(spic::Point(0.0f, 100.0f), 0.0f, 1.0f));
	AddContent(titleText);

	spic::DataHandler dataHandler = spic::DataHandler("jenga_settings");
	std::map<std::string, std::string> settings;
	settings["difficulty"] = std::to_string(static_cast<int>(WinCondition::EASY));
	dataHandler.AddSettings(settings);
	dataHandler.Save();

	AddButton("easyBtn", "Easy", [this]() {
		this->buttons["easyBtn"]->GetComponent<Sprite>()->Color(spic::Color::green());
		this->buttons["mediumBtn"]->GetComponent<Sprite>()->Color(spic::Color::white());
		this->buttons["hardBtn"]->GetComponent<Sprite>()->Color(spic::Color::white());
		spic::DataHandler dataHandler = spic::DataHandler("jenga_settings");
		std::map<std::string, std::string> settings;
		settings["difficulty"] = std::to_string(static_cast<int>(WinCondition::EASY));
		dataHandler.AddSettings(settings);
		dataHandler.Save();
		}, -50.0f);

	AddButton("mediumBtn", "Medium", [this]() {
		this->buttons["easyBtn"]->GetComponent<Sprite>()->Color(spic::Color::white());
		this->buttons["mediumBtn"]->GetComponent<Sprite>()->Color(spic::Color::green());
		this->buttons["hardBtn"]->GetComponent<Sprite>()->Color(spic::Color::white());
		spic::DataHandler dataHandler = spic::DataHandler("jenga_settings");
		std::map<std::string, std::string> settings;
		settings["difficulty"] = std::to_string(static_cast<int>(WinCondition::NORMAL));
		dataHandler.AddSettings(settings);
		dataHandler.Save();
		}, 50.0f);

	AddButton("hardBtn", "Hard", [this]() {
		this->buttons["easyBtn"]->GetComponent<Sprite>()->Color(spic::Color::white());
		this->buttons["mediumBtn"]->GetComponent<Sprite>()->Color(spic::Color::white());
		this->buttons["hardBtn"]->GetComponent<Sprite>()->Color(spic::Color::green());
		spic::DataHandler dataHandler = spic::DataHandler("jenga_settings");
		std::map<std::string, std::string> settings;
		settings["difficulty"] = std::to_string(static_cast<int>(WinCondition::HARD));
		dataHandler.AddSettings(settings);
		dataHandler.Save();
		}, 150.0f);

	AddButton("startBtn", "Start", [this]() {
		GameEngine::GetInstance()->LoadSceneByName("jenga");
		}, 250.0f);

	this->buttons["easyBtn"]->GetComponent<Sprite>()->Color(spic::Color::green());
}

void DifficultyScene::AddButton(const std::string& name, const std::string& text, std::function<void()> callback, const float offset)
{
	auto button = std::make_shared<spic::Button>(250.0f, 100.0f, text, spic::Color::white(), "assets/textures/buttons/Button22.png");
	button->Name(name);
	button->Transform(std::make_shared<spic::Transform>(spic::Point(500.0f, 260.0f + offset), 0.0f, 1.0f));
	auto textTransform = button->GetChild<spic::Text>()->Transform();
	textTransform->position.y = 35.0f;
	button->OnClick(callback);
	buttons[name] = button;
	AddContent(button);
}

spic::Scene* DifficultyScene::Start()
{
	spic::input::UnSubscribeAll();
	DifficultyScene* a = new DifficultyScene();
	return a;
}