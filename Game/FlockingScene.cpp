#include "FlockingScene.h"
#include <Button.hpp>
#include "CameraMovementScript.h"
#include "CollisionDetectionScript.h"
#include <BoxCollider.hpp>
#include "AudioSource.hpp"
#include "Box.h"
#include <Input.hpp>
#include "AimListener.h"
#include "CircleObstacle.h"

FlockingScene::FlockingScene() : Scene()
{
	SetCamera();
	SetContents();
	LoadTileMap("assets/maps/map.tmx", 3);
}

void FlockingScene::SetCamera()
{
	std::unique_ptr<spic::Camera> camera = std::make_unique<spic::Camera>();
	camera->Transform(std::make_shared<spic::Transform>(spic::Point(0.0f, 0.0f), 0.0f, 1.0f));
	camera->BackgroundColor(spic::Color::blue());
	camera->AddComponent(std::make_shared<CameraMovementScript>());
	Camera(std::move(camera));
}

void FlockingScene::SetContents()
{
	/* Rocket launcher setup */
	std::shared_ptr<spic::GameObject> rocketLauncher = std::make_shared<spic::GameObject>();
	std::string rocketLauncherName = "rocketLauncher";
	std::shared_ptr<spic::Transform> rocketLauncherTransform = std::make_shared<spic::Transform>();
	rocketLauncherTransform->rotation = 0.0f;
	rocketLauncherTransform->position = { 700.0f, 375.0f };
	rocketLauncherTransform->scale = 0.25f;
	auto rocketLauncherSprite = std::make_shared<spic::Sprite>("assets/textures/rocket-launcher.png", 1);
	rocketLauncher->Name(rocketLauncherName);
	rocketLauncher->Transform(rocketLauncherTransform);
	rocketLauncher->AddComponent<spic::Sprite>(rocketLauncherSprite);
	std::shared_ptr<AimListener> aimListener = std::make_shared<AimListener>(rocketLauncher);
	spic::Input::Subscribe(spic::Input::MouseButton::LEFT, aimListener);

	/* Obstacles setup */
	spic::Point obstaclePosition = { 300.0f, 200.0f };
	std::shared_ptr<CircleObstacle> obstacle = std::make_shared<CircleObstacle>("blade1", obstaclePosition);

	AddContent(rocketLauncher);
	AddContent(obstacle);
}