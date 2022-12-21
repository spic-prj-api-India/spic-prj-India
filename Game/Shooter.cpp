#include "Shooter.h"
#include <Sprite.hpp>
#include "AimListener.h"
#include <Input.hpp>

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
	Transform(std::make_shared<spic::Transform>(position, 0.0f, 0.25f));
	auto rocketLauncherSprite = std::make_shared<spic::Sprite>("assets/textures/rocket-launcher.png", 1);
	AddComponent<spic::Sprite>(rocketLauncherSprite);
}

void Shooter::SetContent(std::map<std::string, std::string>& data)
{

}

void Shooter::SetListener()
{
	std::shared_ptr<AimListener> aimListener = std::make_shared<AimListener>(this);
	spic::input::Subscribe(spic::input::MouseButton::LEFT, aimListener);
}