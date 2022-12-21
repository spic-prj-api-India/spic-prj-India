#include "LoseScene.h"
#include "BackScript.h"
#include <Text.hpp>
#include "Input.hpp"

LoseScene::LoseScene() : Scene()
{
	SetCamera();
	SetContents();
}

void LoseScene::SetCamera()
{
	std::unique_ptr<spic::Camera> camera = std::make_unique<spic::Camera>();
	camera->Transform(std::make_shared<spic::Transform>(spic::Point(0.0f, 0.0f), 0.0f, 1.0f));
	camera->BackgroundColor(spic::Color::blue());
	camera->AddComponent<spic::BehaviourScript>(std::make_shared<BackScript>());
	Camera(std::move(camera));
}

void LoseScene::SetContents()
{
	auto text = std::make_shared<spic::Text>(1200.0f, 900.0f
		, "Congratulations\nYou've played yourself\n"
		, ""
		, 50
		, spic::Alignment::CENTER
		, spic::Color::white());

	text->Transform(std::make_shared<spic::Transform>(spic::Point(0.0f, 0.0f), 0.0f, 1.0f));
	AddContent(text);
}

spic::Scene* LoseScene::Start()
{
	spic::input::ResetSubscribedEvents();
	LoseScene* a = new LoseScene();
	return a;
}