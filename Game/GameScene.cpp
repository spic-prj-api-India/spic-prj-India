#include "GameScene.h"
#include <Button.hpp>
#include "CameraMovementScript.h"
#include "CollisionDetectionScript.h"
#include <BoxCollider.hpp>
#include "AudioSource.hpp"
#include "Box.h"

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
	std::shared_ptr<Box> box2 = std::make_shared<Box>();
	std::shared_ptr<Box> box3 = std::make_shared<Box>();

	std::string boxName = "box";
	std::string boxName2 = "box2";
	std::string boxName3 = "box3";

	std::shared_ptr<spic::Transform> boxTransform = std::make_shared<spic::Transform>();
	boxTransform->position = { 75.0f, 24.0f };
	boxTransform->rotation = 0.785f;
	boxTransform->scale = 5.0f;

	std::shared_ptr<spic::Transform> boxTransform2 = std::make_shared<spic::Transform>();
	boxTransform2->position = { 400.0f, 50.0f };
	boxTransform2->rotation = 0.785f;
	boxTransform2->scale = 5.0f;
	std::shared_ptr<spic::Transform> boxTransform3 = std::make_shared<spic::Transform>();
	boxTransform3->position = { 500.0f, 50.0f };
	boxTransform3->rotation = 0.785f;
	boxTransform3->scale = 5.0f;

	std::shared_ptr<spic::BoxCollider> boxCollider = std::make_shared<spic::BoxCollider>();
	boxCollider->Width(45.0f);
	boxCollider->Height(45.0f);
	std::shared_ptr<spic::RigidBody> boxRigidBody = std::make_shared<spic::RigidBody>(1.0f, 1.0f, spic::BodyType::dynamicBody);
	std::shared_ptr<CollisionDetectionScript> script = std::make_shared<CollisionDetectionScript>();
	auto boxSprite = std::make_shared<spic::Sprite>("assets/textures/box.png", 1);
	auto music = std::make_shared<spic::AudioSource>("assets/music/file_example_MP3_700KB.mp3", true, true, 1.0f);

	box->Name(boxName);
	box->Transform(boxTransform);
	box2->Name(boxName2);
	box2->Transform(boxTransform2);
	box3->Name(boxName3);
	box3->Transform(boxTransform3);
	
	box->AddComponent<spic::BoxCollider>(boxCollider);
	box->AddComponent<spic::RigidBody>(boxRigidBody);
	box->AddComponent<spic::BehaviourScript>(script);
	box->AddComponent<spic::Sprite>(boxSprite);
	box->AddComponent<spic::AudioSource>(music);
	box2->AddComponent<spic::BoxCollider>(boxCollider);
	box2->AddComponent<spic::RigidBody>(boxRigidBody);
	box2->AddComponent<spic::BehaviourScript>(script);
	box2->AddComponent<spic::Sprite>(boxSprite);
	box3->AddComponent<spic::BoxCollider>(boxCollider);
	box3->AddComponent<spic::RigidBody>(boxRigidBody);
	box3->AddComponent<spic::BehaviourScript>(script);
	box3->AddComponent<spic::Sprite>(boxSprite);

	//UI test
	std::shared_ptr<spic::Button> button = std::make_shared<spic::Button>(200.0f, 100.0f, "Click me");
	button->Transform(std::make_shared<spic::Transform>(spic::Point(20.0f, 20.0f), 0.0f, 1.0f));
	button->OnClick([]() {
		std::cout << "Button clicked" << std::endl;
		});

	// Save Scene Button
	std::shared_ptr<spic::Button> saveButton = std::make_shared<spic::Button>(200.0f, 100.0f, "Save Scene");
	saveButton->Transform(std::make_shared<spic::Transform>(spic::Point(150.0f, 20.0f), 0.0f, 1.0f));
	saveButton->OnClick([]() {
		std::cout << "Button clicked" << std::endl;
		});

	AddContent(box);
	AddContent(box2);
	AddContent(box3);
	AddContent(button);
	AddContent(std::make_shared<Box>());
}