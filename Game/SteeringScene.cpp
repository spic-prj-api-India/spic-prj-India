#include "SteeringScene.h"
#include <Button.hpp>
#include "CameraMovementScript.h"
#include "CollisionDetectionScript.h"
#include <BoxCollider.hpp>
#include "AudioSource.hpp"
#include <Input.hpp>
#include "AimListener.h"
#include "CircleObstacle.h"
#include "BackScript.h"

SteeringScene::SteeringScene() : Scene()
{
	SetCamera();
	SetContents();
	LoadTileMap("assets/maps/map3.tmx", 1);
}

void SteeringScene::SetCamera()
{
	std::unique_ptr<spic::Camera> camera = std::make_unique<spic::Camera>();
	camera->Transform(std::make_shared<spic::Transform>(spic::Point(0.0f, 0.0f), 0.0f, 1.0f));
	camera->BackgroundColor(spic::Color::blue());
	camera->AddComponent(std::make_shared<CameraMovementScript>());
	camera->AddComponent<spic::BehaviourScript>(std::make_shared<BackScript>());
	Camera(std::move(camera));
}

void SteeringScene::SetContents()
{
	/* Rocket launcher setup */
	std::shared_ptr<spic::GameObject> rocketLauncher = std::make_shared<spic::GameObject>();
	std::string rocketLauncherName = "rocketLauncher";
	std::shared_ptr<spic::Transform> rocketLauncherTransform = std::make_shared<spic::Transform>();
	rocketLauncherTransform->rotation = 0.0f;
	rocketLauncherTransform->position = { 600.0f, 475.0f };
	rocketLauncherTransform->scale = 0.175f;
	auto rocketLauncherSprite = std::make_shared<spic::Sprite>("assets/textures/rocket-launcher.png", 1);
	rocketLauncher->Name(rocketLauncherName);
	rocketLauncher->Transform(rocketLauncherTransform);
	rocketLauncher->AddComponent<spic::Sprite>(rocketLauncherSprite);
	std::shared_ptr<AimListener> aimListener = std::make_shared<AimListener>(rocketLauncher);
	spic::input::Subscribe(spic::input::MouseButton::LEFT, aimListener);

	/* Obstacles setup */
	spic::Point obstaclePosition = { 300.0f, 200.0f };
	std::shared_ptr<CircleObstacle> obstacle = std::make_shared<CircleObstacle>("blade1", obstaclePosition);

	AddContent(rocketLauncher);
	AddContent(obstacle);
}

spic::Scene* SteeringScene::Start()
{
	spic::input::UnSubscribeAll();
	SteeringScene* a = new SteeringScene();
	return a;
}