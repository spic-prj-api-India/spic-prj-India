#include "Box.h"
#include <Sprite.hpp>
#include <RigidBody.hpp>
#include "BoxCollider.hpp"

Box::Box() : Persistable(this, "Box"), GameObject(), feelerLength{ feelerLength }
{
	SetAttributes({ 0.0f, 0.0f });
}

Box::Box(const std::string& name, const spic::Point& position, const float feelerLength) : 
	Persistable(this, "Box"), GameObject(name), feelerLength{ feelerLength }
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

std::map<std::string, std::function<std::string()>> Box::SaveProperties()
{
	auto saveProperties = Persistable::SaveProperties();
	saveProperties["feelerLength"] = [this]() { return std::to_string(this->feelerLength); };
	return saveProperties;
}

std::map<std::string, std::function<void(const std::string&)>> Box::LoadProperties()
{
	auto loadProperties = Persistable::LoadProperties();
	loadProperties["feelerLength"] = [this](const std::string& feelerLength) { this->feelerLength = std::stof(feelerLength); };
	return loadProperties;
}