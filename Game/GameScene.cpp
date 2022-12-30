#include "GameScene.h"
#include <Button.hpp>
#include "CameraMovementScript.h"
#include "CollisionDetectionScript.h"
#include "AudioSource.hpp"
#include "Ball.h"
#include "PlayerMovementScript.h"
#include <GameEngine.hpp>
#include "BackScript.h"
#include "BoxSpawnerScript.h"
#include <DataHandler.hpp>
#include <Text.hpp>
#include "TimerScript.h"
#include <BoxCollider.hpp>
#include "CheckWinConditionScript.h"

GameScene::GameScene() : Scene()
{
	SetCamera();
	SetContents();
	LoadTileMap("assets/maps/map.tmx", 3);
}

void GameScene::SetCamera()
{
	std::unique_ptr<spic::Camera> camera = std::make_unique<spic::Camera>();
	camera->Transform(std::make_shared<spic::Transform>(spic::Point(0.0f, 0.0f), 0.0f, 1.0f));
	camera->BackgroundColor(spic::Color::blue());
	camera->AddComponent(std::make_shared<CameraMovementScript>());
	camera->AddComponent<spic::BehaviourScript>(std::make_shared<BackScript>());
	auto bloopAudioEffect = std::make_shared<spic::AudioSource>("assets/music/BLOOP_SOUND_EFFECT.mp3", false, false, 0.2f);
	auto script1 = std::make_shared<BoxSpawnerScript>();
	script1->bloopAudio = bloopAudioEffect.get();
	camera->AddComponent(std::move(bloopAudioEffect));
	camera->AddComponent(std::move(script1));

	// Load music setting
	std::map<std::string, std::string> settings;
	spic::DataHandler dataHandler = spic::DataHandler("sound_settings");
	dataHandler.LoadSettings(settings);
	bool backgroundMusic = std::stoi(settings["background_music"]);
	if (backgroundMusic)
	{
		auto music = std::make_shared<spic::AudioSource>("assets/music/8-bit soundtrack.mp3", true, true, 0.3f);
		camera->AddComponent(music);
	}

	Camera(std::move(camera));
}

void GameScene::SetContents()
{
	// Football
	std::shared_ptr<CollisionDetectionScript> collisionScript = std::make_shared<CollisionDetectionScript>();
	std::shared_ptr<PlayerMovementScript> movementScript = std::make_shared<PlayerMovementScript>();

	spic::Point ballPosition = { 400.0f, 24.0f };
	std::shared_ptr<Ball> football = std::make_shared<Ball>("football", ballPosition, "assets/textures/football.png", 0.09765625f);
	auto moveFootballScript = std::make_shared<PlayerMovementScript>(
		spic::input::KeyCode::J, spic::input::KeyCode::L, spic::input::KeyCode::I);
	football->AddComponent<spic::BehaviourScript>(moveFootballScript);

	// Timer
	auto timerText = std::make_shared<spic::Text>(
		static_cast<float>(spic::settings::WINDOW_WIDTH)
		, static_cast<float>(spic::settings::WINDOW_HEIGHT)
		, ""
		, ""
		, 50
		, spic::Alignment::CENTER
		, spic::Color::white());
	timerText->Transform(std::make_shared<spic::Transform>(spic::Point(0.0f, 100.0f), 0.0f, 1.0f));
	timerText->AddComponent(std::make_shared<TimerScript>(timerText));

	// Win line
	int yCondition = static_cast<int>(WinCondition::EASY);
	float lineHeight = 5.0f;
	spic::Point position = {0.0f, static_cast<float>(yCondition) - lineHeight };
	auto line = std::make_shared<spic::UIObject>(static_cast<float>(spic::settings::WINDOW_WIDTH), lineHeight);
	line->Name("WinLine");
	line->Transform(std::make_shared<spic::Transform>(position, 0.0f, 1.0f));
	line->AddComponent<spic::Sprite>(std::make_shared<spic::Sprite>("defaults/textures/Filled_rectangle.png", 1, 0, spic::Color::red()));

	AddContent(football);
	AddContent(timerText);
	AddContent(line);
}

spic::Scene* GameScene::Start()
{
	spic::input::UnSubscribeAll();
	GameScene* a = new GameScene();
	return a;
}
