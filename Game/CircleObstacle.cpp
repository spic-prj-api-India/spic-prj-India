#include "CircleObstacle.h" 
#include <Sprite.hpp>
#include <CircleCollider.hpp>
#include "RigidBody.hpp"
#include <Animator.hpp>

CircleObstacle::CircleObstacle(const std::string& name, const spic::Point& position) : GameObject(name), Obstacle(70.0f)
{
	SetAttributes(position);
}

void CircleObstacle::SetAttributes(const spic::Point& position)
{
	Tag("obstacle");
	auto circleCollider = std::make_shared<spic::CircleCollider>(55.2f);
	Transform(std::make_shared<spic::Transform>(position, 0.0f, 0.2f));
	AddComponent<spic::CircleCollider>(std::move(circleCollider));
	AddComponent<spic::RigidBody>(std::make_shared<spic::RigidBody>(3.0f, 1.0f, spic::BodyType::staticBody));
	auto animator = std::make_shared<spic::Animator>(10);
	animator->InitHorizontalSpriteSheet("assets/textures/circular_saw_spritesheet.png", 4, 548, 552);
	animator->Play(true);
	AddComponent<spic::Animator>(std::move(animator));
}