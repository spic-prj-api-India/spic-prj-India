#include "CircleObstacle.h" 
#include <Sprite.hpp>
#include <CircleCollider.hpp>
#include "RigidBody.hpp"

CircleObstacle::CircleObstacle(const std::string& name, const spic::Point& position) : GameObject(name)
{
	SetAttributes(position);
}

void CircleObstacle::SetAttributes(const spic::Point& position)
{
	Tag("ball");
	auto circleCollider = std::make_shared<spic::CircleCollider>(60.0f);
	Transform(std::make_shared<spic::Transform>(position, 0.0f, 1.0f));
	AddComponent<spic::CircleCollider>(std::move(circleCollider));
	AddComponent<spic::RigidBody>(std::make_shared<spic::RigidBody>(3.0f, 1.0f, spic::BodyType::staticBody));
	auto sprite = std::make_shared<spic::Sprite>("assets/textures/bladespritesheet.png", 1, 0, spic::Color::white(), false, false, 0,0, 115, 120);
	AddComponent<spic::Sprite>(std::move(sprite));
}