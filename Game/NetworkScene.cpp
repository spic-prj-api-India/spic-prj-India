#include "NetworkScene.h"
#include <Button.hpp>
#include "NetworkBackScript.h"
#include <Input.hpp>
#include "CircleObstacle.h"
#include <DataHandler.hpp>
#include "Shooter.h"
#include "SyncScript.h"
#include "Target.h"
#include <Text.hpp>
#include <Animator.hpp>
#include "Settings.hpp"
#include "LoadingAnimation.h"

NetworkScene::NetworkScene() : Scene()
{
	SetCamera();
	SetContents();
	LoadTileMap("assets/maps/map.tmx", 3);
}

void NetworkScene::SetCamera()
{
	std::unique_ptr<spic::Camera> camera = std::make_unique<spic::Camera>();
	camera->Transform(std::make_shared<spic::Transform>(spic::Point(0.0f, 0.0f), 0.0f, 1.0f));
	camera->BackgroundColor(spic::Color::blue());
	Camera(std::move(camera));
}

void NetworkScene::SetContents()
{
	/* Shooter setup */
	spic::Point shooterPosition = { 700.0f, 375.0f };
	std::shared_ptr<Shooter> shooter = std::make_shared<Shooter>(shooterPosition);
	shooter->AddComponent<spic::SocketScript>(std::make_shared<SyncScript>());
	shooter->AddComponent(std::make_shared<NetworkBackScript>());

	/* Target setup */
	spic::Point targetPosition = { 50.0f, 50.0f };
	std::shared_ptr<Target> target = std::make_shared<Target>(targetPosition);

	/* Obstacles setup */
	spic::Point obstaclePosition = { 300.0f, 200.0f };
	std::shared_ptr<CircleObstacle> obstacle = std::make_shared<CircleObstacle>("blade1", obstaclePosition);

	/* Loading animations */
	auto position = spic::Point(300.0f, 300.0f);
	auto loadingAnimation = std::make_shared<LoadingAnimation>("loadingAnimation", position,
		"Is looking for opponent");
	auto exitAnimation = std::make_shared<LoadingAnimation>("exitAnimation", position,
		"Opponent left, waiting for opponent", false);

	/* Add contents */
	AddContent(loadingAnimation);
	AddContent(exitAnimation);
	AddContent(shooter);
	AddContent(target);
	AddContent(obstacle);
}

spic::Scene* NetworkScene::Start()
{
	spic::input::UnSubscribeAll();
	NetworkScene* a = new NetworkScene();
	return a;
}