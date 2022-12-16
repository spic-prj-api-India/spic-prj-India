#include "Ball.h"
#include <Sprite.hpp>
#include <Point.cpp>
#include <CircleCollider.hpp>
#include "RigidBody.hpp"

Ball::Ball(const std::string& name, const spic::Point& position, const std::string& sprite, const float scale) : GameObject(name)
{
	SetAttributes(position, sprite, scale);
}

void Ball::SetAttributes(const spic::Point& position, const std::string& sprite, const float scale)
{
	Tag("ball");
	auto circleCollider = std::make_shared<spic::CircleCollider>(25.0f);
	Transform(std::make_shared<spic::Transform>(position, 0.0f, scale));
	AddComponent<spic::CircleCollider>(std::move(circleCollider));
	AddComponent<spic::RigidBody>(std::make_shared<spic::RigidBody>(3.0f, 1.0f, spic::BodyType::dynamicBody));
	AddComponent<spic::Sprite>(std::make_shared<spic::Sprite>(sprite, 1));
}
