#include "WinScene.h"
#include "BackScript.h"
#include <Text.hpp>
#include <Input.hpp>

WinScene::WinScene() : Scene()
{
	SetCamera();
	SetContents();
}

void WinScene::SetCamera()
{
	std::unique_ptr<spic::Camera> camera = std::make_unique<spic::Camera>();
	camera->Transform(std::make_shared<spic::Transform>(spic::Point(0.0f, 0.0f), 0.0f, 1.0f));
	camera->BackgroundColor(spic::Color::blue());
	camera->AddComponent<spic::BehaviourScript>(std::make_shared<BackScript>());
	Camera(std::move(camera));
}

void WinScene::SetContents()
{
	auto text = std::make_shared<spic::Text>(1200.0f, 900.0f
		, "Congratulations\nYou have won the game\n"
		, ""
		, 50
		, spic::Alignment::CENTER
		, spic::Color::white());

	text->Transform(std::make_shared<spic::Transform>(spic::Point(0.0f, 0.0f), 0.0f, 1.0f));
	AddContent(text);
}

spic::Scene* WinScene::Start()
{
	spic::input::ResetSubscribedEvents();
	WinScene* a = new WinScene();
	return a;
}