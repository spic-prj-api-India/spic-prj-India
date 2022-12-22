#include "FlockingScene.h"
#include <Button.hpp>
#include "CameraMovementScript.h"
#include "CollisionDetectionScript.h"
#include <BoxCollider.hpp>
#include "AudioSource.hpp"
#include <Input.hpp>
#include "AimListener.h"
#include "CircleObstacle.h"
#include <DataHandler.hpp>
#include "Shooter.h"
#include "SyncScript.h"
#include "Target.h"

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
	/* Shooter setup */
	spic::Point shooterPosition = { 700.0f, 375.0f };
	std::shared_ptr<Shooter> shooter = std::make_shared<Shooter>(shooterPosition);
	auto script = std::make_shared<SyncScript>();
	shooter->AddComponent<spic::SocketScript>(script);

	/* Target setup */
	spic::Point targetPosition = { 50.0f, 50.0f };
	std::shared_ptr<Target> target = std::make_shared<Target>(targetPosition);

	/* Obstacles setup */
	spic::Point obstaclePosition = { 300.0f, 200.0f };
	std::shared_ptr<CircleObstacle> obstacle = std::make_shared<CircleObstacle>("blade1", obstaclePosition);

	AddContent(shooter);
	AddContent(target);
	AddContent(obstacle);
}

spic::Scene* FlockingScene::Start()
{
	spic::input::UnSubscribeAll();
	FlockingScene* a = new FlockingScene();
	return a;
}