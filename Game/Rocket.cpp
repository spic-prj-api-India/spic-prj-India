#include "Rocket.h"
#include <BoxCollider.hpp>
#include <Sprite.hpp>

Rocket::Rocket(const std::string& name, const spic::Point& position, const float angle) : ForceDriven(spic::SumMethod::WEIGHTED_AVERAGE, 0.15f, 1.0f, 0.122173048f)
{
	SetAttributes(name, position, angle);
	SetWeights();
}

void Rocket::SetAttributes(const std::string& name, const spic::Point& position, const float angle)
{
	Name(name);
	Tag("rocket");
	auto boxCollider = std::make_shared<spic::BoxCollider>(20.0f, 70.0f);
	//boxCollider->Disable();
	Transform(std::make_shared<spic::Transform>(position, angle, 0.125f));
	AddComponent<spic::BoxCollider>(std::move(boxCollider));
	rigidBody = std::make_shared<spic::RigidBody>(3.0f, 1.0f, spic::BodyType::dynamicBody);
	AddComponent<spic::RigidBody>(rigidBody);
	AddComponent<spic::Sprite>(std::make_shared<spic::Sprite>("assets/textures/missile.png", 1));
}

void Rocket::SetWeights()
{
	//UseArrival({}, spic::Deceleration::NORMAL);
	UseSeek({});
	//UseFlee({});
	//UseWander(1.0f, 1.0f, 1.1f, 60.0f);

	Seperation(1.0f, 24.0f);
	Alignment(0.25f, 125.0f);
	Cohesion(0.25f, 125.0f);
	WallAvoidance(1.5f, 20.0f, spic::Point(1200.0f, 800.0f));
}