#include "Rocket.h"
#include <BoxCollider.hpp>
#include <Sprite.hpp>

Rocket::Rocket(const std::string& name, const spic::Point& position, const float angle) : ForceDriven(spic::SumMethod::WEIGHTED_AVERAGE, 0.5f, 1.5f, 0.122173048f)
{
	SetAttributes(name, position, angle);
	SetSteeringBehaviours();
	SetGroupBehaviours();
}

void Rocket::SetAttributes(const std::string& name, const spic::Point& position, const float angle)
{
	Name(name);
	Tag("rocket");
	auto boxCollider = std::make_shared<spic::BoxCollider>(20.0f, 70.0f);
	boxCollider->Disable();
	Transform(std::make_shared<spic::Transform>(position, angle, 0.125f));
	AddComponent<spic::BoxCollider>(std::move(boxCollider));
	rigidBody = std::make_shared<spic::RigidBody>(3.0f, 0.0f, spic::BodyType::dynamicBody);
	AddComponent<spic::RigidBody>(rigidBody);
	AddComponent<spic::Sprite>(std::make_shared<spic::Sprite>("assets/textures/missile.png", 1));
}

void Rocket::SetSteeringBehaviours()
{
	SetDeceleration(spic::Deceleration::SLOW);
	//Wander(.5f, 1.1f, 6.0f, 60.0f);
	WallAvoidance(3.0f, 80.0f, spic::Point(1200.0f, 800.0f));
	ObstacleAvoidance(3.0f, 80.0f);
}

void Rocket::SetGroupBehaviours()
{
	Seperation(0.5f, 40.0f);
	Alignment(0.5f, 125.0f);
	Cohesion(0.5f, 125.0f);
}