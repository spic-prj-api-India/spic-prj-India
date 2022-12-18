#include "Box.h"
#include <Sprite.hpp>
#include <RigidBody.hpp>
#include "BoxCollider.hpp"

Box::Box(const std::string& name, const spic::Point& position) : Persistable(this), GameObject(name)
{
	SetAttributes(position);
}

void Box::SetAttributes(const spic::Point& position)
{
	Tag("box");
	Transform(std::make_shared<spic::Transform>(position, 0.0f, 5.0f));
	AddComponent<spic::Sprite>(std::make_shared<spic::Sprite>("assets/textures/box.png", 1));
	AddComponent<spic::BoxCollider>(std::make_shared<spic::BoxCollider>(50.0f, 50.0f));
	AddComponent<spic::RigidBody>(std::make_shared<spic::RigidBody>(10.0f, 1.0f, spic::BodyType::dynamicBody));
}