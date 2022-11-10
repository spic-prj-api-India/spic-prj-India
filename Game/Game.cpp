// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "GameEngine.hpp"
#include <PhysicsSystem.hpp>
#include <BoxCollider.hpp>
#include <Box2DExtension.hpp>

int main()
{
	GameEngine* engine = GameEngine::GetInstance();
	std::shared_ptr<extensions::Box2DExtension> physicsExtension = std::make_shared<extensions::Box2DExtension>();
	engine->AddExtension(physicsExtension);
	systems::PhysicsSystem system = systems::PhysicsSystem();

	std::shared_ptr<spic::GameObject> entity = std::make_shared<spic::GameObject>();
	std::string tag = "box";
	std::shared_ptr<spic::Transform> transform = std::make_shared<spic::Transform>();
	transform->position = { -2.5f, -2.5f };
	transform->rotation = 45.0f;
	transform->scale = 1.0f;
	std::shared_ptr<spic::BoxCollider> boxCollider = std::make_shared<spic::BoxCollider>();
	boxCollider->Width(0.3f);
	boxCollider->Height(0.3f);
	std::shared_ptr<spic::RigidBody> rigidBody = std::make_shared<spic::RigidBody>(1.0f, 0.2f, spic::BodyType::dynamicBody);

	entity->Tag(tag);
	entity->Transform(transform);
	entity->AddComponent<spic::BoxCollider>(boxCollider);
	entity->AddComponent<spic::RigidBody>(rigidBody);

	std::vector< std::shared_ptr<spic::GameObject>> entities = std::vector< std::shared_ptr<spic::GameObject>>();
	entities.emplace_back(entity);
	while (true) {
		system.Update(entities);
		std::cout << "x: " << entity->Transform()->position.x << ", y: " << entity->Transform()->position.y << std::endl;
	}
}