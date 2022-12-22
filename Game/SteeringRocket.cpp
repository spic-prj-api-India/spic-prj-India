#include "SteeringRocket.h"
#include <BoxCollider.hpp>
#include <Sprite.hpp>
#include <Flocking.hpp>
#include <Steering.hpp>

SteeringRocket::SteeringRocket(const std::string& name, const spic::Point& position, const float angle) : ForceDriven(spic::SumMethod::WEIGHTED_AVERAGE, 0.5f, 1.5f, 0.122173048f, 40.0f)
{
	SetAttributes(name, position, angle);
	SetSteeringBehaviours();
	SetGroupBehaviours();
}

void SteeringRocket::SetAttributes(const std::string& name, const spic::Point& position, const float angle)
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

void SteeringRocket::SetSteeringBehaviours()
{
	std::shared_ptr<spic::Steering> steering = std::make_shared<spic::Steering>(this);

	steering->SetDeceleration(spic::Deceleration::SLOW);
	//steering->WanderOn(.5f, 1.1f, 6.0f, 60.0f);
	steering->WallAvoidanceOn(3.0f, 80.0f, spic::Point(1200.0f, 800.0f));
	steering->ObstacleAvoidanceOn(3.0f, 120.0f);
	AddComponent<spic::Steering>(steering);
}

void SteeringRocket::SetGroupBehaviours()
{
	std::shared_ptr<spic::Flocking> flocking = std::make_shared<spic::Flocking>(this);
	flocking->SeperationOn(0.20f, 60.0f);
	flocking->AlignmentOn(0.20f, 125.0f);
	flocking->CohesionOn(0.20f, 125.0f);
	AddComponent<spic::Flocking>(flocking);
}