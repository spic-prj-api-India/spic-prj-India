#include "Rocket.h"
#include <BoxCollider.hpp>
#include <Sprite.hpp>
#include <Flocking.hpp>
#include <Steering.hpp>

Rocket::Rocket(const std::string& name) : GameObject(name)
{
	SetAttributes();
}

void Rocket::SetAttributes()
{
	Tag("rocket");
	auto boxCollider = std::make_shared<spic::BoxCollider>(20.0f, 70.0f);
	boxCollider->Disable();
	AddComponent<spic::BoxCollider>(std::move(boxCollider));
	AddComponent<spic::RigidBody>(std::make_shared<spic::RigidBody>(1.0f, 0.0f, spic::BodyType::staticBody));
	AddComponent<spic::Sprite>(std::make_shared<spic::Sprite>("assets/textures/missile.png", 1));
}