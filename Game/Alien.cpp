#include "Alien.h"
#include <BoxCollider.hpp>
#include <Sprite.hpp>
#include <Steering.hpp>
#include <DataHandler.hpp>

Alien::Alien(const std::string& name, const spic::Point& position, const float angle) : 
	ForceDriven(spic::SumMethod::WEIGHTED_AVERAGE, 0.5f, 0.5f, 0.122173048f, 40.0f)
{
	SetAttributes(name, position, angle);
	SetSteeringBehaviours();
	StartForceDrivenEntity();
}

void Alien::SetAttributes(const std::string& name, const spic::Point& position, const float angle)
{
	Name(name);
	Tag("alien");
	auto boxCollider = std::make_shared<spic::BoxCollider>(20.6f, 42.4f);
	boxCollider->Disable();
	Transform(std::make_shared<spic::Transform>(position, angle, 0.2f));
	AddComponent<spic::BoxCollider>(std::move(boxCollider));
	auto rigidBody = std::make_shared<spic::RigidBody>(3.0f, 0.0f, spic::BodyType::dynamicBody);
	AddComponent<spic::RigidBody>(rigidBody);
	AddComponent<spic::Sprite>(std::make_shared<spic::Sprite>("assets/textures/alien1.png", 1));
}

void Alien::SetSteeringBehaviours()
{
	std::shared_ptr<spic::Steering> steering = std::make_shared<spic::Steering>(this);

	steering->WanderOn(.5f, 1.1f, 6.0f, 60.0f);
	steering->WallAvoidanceOn(3.0f, 50.0f, spic::Point(1200.0f, 800.0f));

	AddComponent<spic::Steering>(steering);
}