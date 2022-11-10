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
	std::unique_ptr<spic::Transform> transform = std::make_unique<spic::Transform>();
	transform->position = { -2.5f, -2.5f };
	transform->rotation = 45.0f;
	transform->scale = 1.0f;
	spic::BoxCollider* boxCollider = new spic::BoxCollider();
	boxCollider->Width(0.3f);
	boxCollider->Height(0.3f);
	std::unique_ptr<spic::RigidBody> rigidBody = std::make_unique<spic::RigidBody>(1.0f, 0.2f, spic::BodyType::dynamicBody);

	entity->SetTag(tag);
	entity->SetTransform(std::move(transform));
	entity->SetCollider(boxCollider);
	entity->SetRigidBody(std::move(rigidBody));

	std::vector< std::shared_ptr<spic::GameObject>> entities = std::vector< std::shared_ptr<spic::GameObject>>();
	entities.emplace_back(entity);
	system.Update(entities);
	std::cout << "Hello World!\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
