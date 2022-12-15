#include "GameScene.h"
#include <Button.hpp>
#include "CameraMovementScript.h"
#include "CollisionDetectionScript.h"
#include <BoxCollider.hpp>
#include "AudioSource.hpp"
#include "Box.h"
#include <RigidBody.hpp>
#include "PlayerMovementScript.h"
#include <CircleCollider.hpp>
#include "Ball.h"
#include <GameEngine.hpp>

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
	Camera(std::move(camera));
}

void GameScene::SetContents()
{
	std::shared_ptr<spic::GameObject> box = std::make_shared<spic::GameObject>();
	std::string boxName = "box";
	std::shared_ptr<spic::Transform> boxTransform = std::make_shared<spic::Transform>();
	boxTransform->position = { 180.0f, 24.0f };
	boxTransform->rotation = 0.0f;
	boxTransform->scale = 5.0f;
	std::shared_ptr<spic::BoxCollider> boxCollider = std::make_shared<spic::BoxCollider>();
	boxCollider->Width(50.0f);
	boxCollider->Height(50.0f);
	std::shared_ptr<spic::RigidBody> boxRigidBody = std::make_shared<spic::RigidBody>(10.0f, 1.0f, spic::BodyType::dynamicBody);
	std::shared_ptr<CollisionDetectionScript> collisionScript = std::make_shared<CollisionDetectionScript>();
	std::shared_ptr<PlayerMovementScript> movementScript = std::make_shared<PlayerMovementScript>();
	auto boxSprite = std::make_shared<spic::Sprite>("assets/textures/box.png", 1);
	auto music = std::make_shared<spic::AudioSource>("assets/music/file_example_MP3_700KB.mp3", true, true, 1.0f);

	box->Name(boxName);
	box->Transform(boxTransform);
	box->AddComponent<spic::BoxCollider>(boxCollider);
	box->AddComponent<spic::RigidBody>(boxRigidBody);
	box->AddComponent<spic::BehaviourScript>(collisionScript);
	box->AddComponent<spic::BehaviourScript>(movementScript);
	box->AddComponent<spic::Sprite>(boxSprite);
	//box->AddComponent<spic::AudioSource>(music);

	spic::Point ballPosition = { 400.0f, 24.0f };
	std::shared_ptr<Ball> football = std::make_shared<Ball>("football", ballPosition, "assets/textures/football.png", 0.09765625f);
	auto moveFootballScript = std::make_shared<PlayerMovementScript>(
		spic::Input::KeyCode::J, spic::Input::KeyCode::L, spic::Input::KeyCode::I);
	football->AddComponent<spic::BehaviourScript>(moveFootballScript);

	//UI test
	std::shared_ptr<spic::Button> button = std::make_shared<spic::Button>(200.0f, 100.0f, "Menu");
	button->Transform(std::make_shared<spic::Transform>(spic::Point(20.0f, 20.0f), 0.0f, 1.0f));
	button->OnClick([]() {
		spic::Input::UnSubscribeAll();

		spic::GameEngine::GetInstance()->LoadSceneByName("menu");
		});

	AddContent(box);
	AddContent(football);
	AddContent(button);
	AddContent(std::make_shared<Box>());
}