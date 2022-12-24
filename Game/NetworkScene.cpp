#include "NetworkScene.h"
#include <Button.hpp>
#include "CameraMovementScript.h"
#include "CollisionDetectionScript.h"
#include <BoxCollider.hpp>
#include "AudioSource.hpp"
#include <Input.hpp>
#include "CircleObstacle.h"
#include <DataHandler.hpp>
#include "Shooter.h"
#include "SyncScript.h"
#include "Target.h"
#include <Text.hpp>
#include <Animator.hpp>
#include "Settings.hpp"

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
	auto script = std::make_shared<SyncScript>();
	shooter->AddComponent<spic::SocketScript>(script);

	/* Target setup */
	spic::Point targetPosition = { 50.0f, 50.0f };
	std::shared_ptr<Target> target = std::make_shared<Target>(targetPosition);

	/* Obstacles setup */
	spic::Point obstaclePosition = { 300.0f, 200.0f };
	std::shared_ptr<CircleObstacle> obstacle = std::make_shared<CircleObstacle>("blade1", obstaclePosition);

	/* Loading animation */
	auto animation = std::make_shared<spic::GameObject>("loadingAnimation");
	animation->Transform(std::make_shared<spic::Transform>(spic::Point(875.0f, 312.5f), 0.0f, .25f));

	auto feedbackText = std::make_shared<spic::Text>(600.0f, 900.0f
		, "Is looking for opponent"
		, ""
		, 50
		, spic::Alignment::CENTER
		, spic::Color::white());
	const float x = (spic::settings::WINDOW_WIDTH / 2.0f) - (feedbackText->Width() / 2);
	feedbackText->Transform(std::make_shared<spic::Transform>(spic::Point(x, 300.0f), 0.0f, 1.0f));
	
	auto animator = std::make_shared<spic::Animator>(60);
	animator->InitSpriteSheet("assets/textures/load_spritesheet.png", 4, 12, 188, 188);
	animator->Play(true);

	animation->AddChild(feedbackText);
	animation->AddComponent(std::move(animator));
	
	/* Add contents */
	AddContent(animation);
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