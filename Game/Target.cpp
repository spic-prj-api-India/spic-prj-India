#include "Target.h"
#include "FollowMouseListener.h"
#include <Input.hpp>
#include <Sprite.hpp>
#include <CircleCollider.hpp>
#include <RigidBody.hpp>

Target::Target()
{

}

Target::Target(const spic::Point& position)
{
	SetAttributes(position);
}

void Target::SetAttributes(const spic::Point& position)
{
	Name("Target");
	Tag("player");
	Transform(std::make_shared<spic::Transform>(position, 0.0f, 0.15f));
	auto mouseSprite = std::make_shared<spic::Sprite>("assets/textures/cursor.png", 1);
	AddComponent<spic::Sprite>(mouseSprite);
	AddComponent<spic::RigidBody>(std::make_shared<spic::RigidBody>(1.0f, 1.0f, spic::BodyType::staticBody));
	AddComponent<spic::CircleCollider>(std::make_shared<spic::CircleCollider>(23.75f));
}

void Target::SetContent(std::map<std::string, std::string>& data)
{

}

void Target::Init()
{
	spic::input::Subscribe(spic::input::MouseButton::LEFT, std::make_shared<FollowMouseListener>(Transform()->position));
}