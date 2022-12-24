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

	/* Loading animation */
	auto loadingAnimation = std::make_shared<spic::GameObject>("loadingAnimation");
	loadingAnimation->Transform(std::make_shared<spic::Transform>(spic::Point(875.0f, 312.5f), 0.0f, .25f));

	auto feedbackText1 = std::make_shared<spic::Text>(600.0f, 900.0f
		, "Is looking for opponent"
		, ""
		, 50
		, spic::Alignment::CENTER
		, spic::Color::white());
	float x = (spic::settings::WINDOW_WIDTH / 2.0f) - (feedbackText1->Width() / 2);
	feedbackText1->Transform(std::make_shared<spic::Transform>(spic::Point(-600.0f, -12.5f), 0.0f, 1.0f));
	
	auto animator1 = std::make_shared<spic::Animator>(60);
	animator1->InitSpriteSheet("assets/textures/load_spritesheet.png", 4, 12, 188, 188);
	animator1->Play(true);

	loadingAnimation->AddChild(feedbackText1);
	loadingAnimation->AddComponent(std::move(animator1));

	/* exit animation */
	auto exitAnimation = std::make_shared<spic::GameObject>("exitAnimation");
	exitAnimation->Transform(std::make_shared<spic::Transform>(spic::Point(875.0f, 312.5f), 0.0f, .25f));
	exitAnimation->Active(false);

	auto feedbackText2 = std::make_shared<spic::Text>(700.0f, 900.0f
		, "Opponent left, waiting for opponent"
		, ""
		, 40
		, spic::Alignment::CENTER
		, spic::Color::white());
	feedbackText2->Transform(std::make_shared<spic::Transform>(spic::Point(-725.0f, -7.25f), 0.0f, 1.0f));

	auto animator2 = std::make_shared<spic::Animator>(60);
	animator2->InitSpriteSheet("assets/textures/load_spritesheet.png", 4, 12, 188, 188);
	animator2->Play(true);

	exitAnimation->AddChild(feedbackText2);
	exitAnimation->AddComponent(std::move(animator2));

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