#include "GameScene.h"
#include <Button.hpp>
#include "CameraMovementScript.h"
#include "CollisionDetectionScript.h"
#include "AudioSource.hpp"
#include "Box.h"
#include "Ball.h"
#include "PlayerMovementScript.h"
#include <GameEngine.hpp>
#include "BackScript.h"

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
	Camera(std::move(camera));
}

void GameScene::SetContents()
{
	spic::Point box1Position = { 75.0f, 24.0f };
	std::shared_ptr<Box> box1 = std::make_shared<Box>("box1", box1Position);
	spic::Point box2Position = { 400.0f, 50.0f };
	std::shared_ptr<Box> box2 = std::make_shared<Box>("box2", box2Position);
	spic::Point box3Position = { 500.0f, 50.0f };
	std::shared_ptr<Box> box3 = std::make_shared<Box>("box3", box3Position);
	box1->AddChild(box2);
	box2->AddChild(box3);

	std::shared_ptr<CollisionDetectionScript> collisionScript = std::make_shared<CollisionDetectionScript>();
	std::shared_ptr<PlayerMovementScript> movementScript = std::make_shared<PlayerMovementScript>();
	auto music = std::make_shared<spic::AudioSource>("assets/music/file_example_MP3_700KB.mp3", true, true, 1.0f);
	//box->AddComponent<spic::AudioSource>(music);

	spic::Point ballPosition = { 400.0f, 24.0f };
	std::shared_ptr<Ball> football = std::make_shared<Ball>("football", ballPosition, "assets/textures/football.png", 0.09765625f);
	auto moveFootballScript = std::make_shared<PlayerMovementScript>(
		spic::input::KeyCode::J, spic::input::KeyCode::L, spic::input::KeyCode::I);
	football->AddComponent<spic::BehaviourScript>(moveFootballScript);

	//UI test
	std::shared_ptr<spic::Button> button = std::make_shared<spic::Button>(200.0f, 100.0f, "Save scene");
	button->Transform(std::make_shared<spic::Transform>(spic::Point(20.0f, 20.0f), 0.0f, 1.0f));
	button->OnClick([]() {
		std::cout << "Scene saved!" << std::endl;
		spic::GameEngine::GetInstance()->SaveScene("game");
		spic::input::UnSubscribeAll();

		spic::GameEngine::GetInstance()->LoadSceneByName("menu");
		});

	AddContent(box1);
	AddContent(box2);
	AddContent(box3);
	AddContent(football);
	AddContent(button);
}

spic::Scene* GameScene::Start()
{
	spic::input::ResetSubscribedEvents();
	GameScene* a = new GameScene();
	return a;
}
