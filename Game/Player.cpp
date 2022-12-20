#include "Player.h"
#include <Sprite.hpp>
#include "AimListener.h"
#include <Input.hpp>

Player::Player() : GameObject()
{

}

Player::Player(const spic::Point& position, const bool isShooter = true) : GameObject()
{
	SetAttributes(position);
}

void Player::SetAttributes(const spic::Point& position)
{
	Tag("Player");
	Transform(std::make_shared<spic::Transform>(position, 0.0f, 1.0f));
	if (this->isShooter) {
		auto rocketLauncherSprite = std::make_shared<spic::Sprite>("assets/textures/rocket-launcher.png", 1);
		AddComponent<spic::Sprite>(rocketLauncherSprite);
		std::shared_ptr<AimListener> aimListener = std::make_shared<AimListener>(this);
		spic::input::Subscribe(spic::input::MouseButton::LEFT, aimListener);
	}
}

void Player::SetContent(std::map<std::string, std::string>& data)
{

}

bool Player::IsShooter() const
{
	return this->isShooter;
}