#include "Shooter.h"
#include <Sprite.hpp>
#include "NetAimListener.h"
#include <Input.hpp>
#include <Text.hpp>

Shooter::Shooter() : GameObject()
{

}

Shooter::Shooter(const spic::Point& position) : GameObject()
{
	SetAttributes(position);
}

void Shooter::SetAttributes(const spic::Point& position)
{
	Name("Shooter");
	Tag("player");
	Transform(std::make_shared<spic::Transform>(position, 0.0f, 0.175f));
	auto rocketLauncherSprite = std::make_shared<spic::Sprite>("assets/textures/rocket-launcher.png", 1);
	AddComponent<spic::Sprite>(rocketLauncherSprite);
}

void Shooter::SetContent(std::map<std::string, std::string>& data)
{

}

void Shooter::Init()
{
	auto text = std::make_shared<spic::Text>(1200.0f, 900.0f
		, "Rockets left: 5"
		, ""
		, 20
		, spic::Alignment::LEFT
		, spic::Color::white());

	text->Transform(std::make_shared<spic::Transform>(spic::Point(0.0f, 0.0f), 0.0f, 1.0f));
	GameObject::Create(text);
	std::shared_ptr<NetAimListener> aimListener = std::make_shared<NetAimListener>(this, text);
	spic::input::Subscribe(spic::input::MouseButton::LEFT, aimListener);
}