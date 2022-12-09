#include "Rocket.h"
#include <BoxCollider.hpp>
#include <Sprite.hpp>

Rocket::Rocket(const std::string& name, const spic::Point& position, const float angle) : Flock(spic::FlockBehaviour::SEEK, 0.05f, 1.0f)
{
	SetAttributes(name, position, angle);
	SetWeights();
}

void Rocket::SetAttributes(const std::string& name, const spic::Point& position, const float angle)
{
	Name(name);
	Tag("rocket");
	Transform(std::make_shared<spic::Transform>(position, angle, 0.125f));
	AddComponent<spic::BoxCollider>(std::make_shared<spic::BoxCollider>(25.5f, 75.0f));
	rigidBody = std::make_shared<spic::RigidBody>(0.75f, 1.0f, spic::BodyType::dynamicBody);
	AddComponent<spic::RigidBody>(rigidBody);
	AddComponent<spic::Sprite>(std::make_shared<spic::Sprite>("assets/textures/missile.png", 1));
}

void Rocket::SetWeights()
{
	/*Seperation(1.5f, 24.0f);
	Alignment(1.0f, 125.0f);
	Cohesion(1.0f, 125.0f);*/
}