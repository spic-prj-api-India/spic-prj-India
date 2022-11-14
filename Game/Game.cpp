// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

std::vector< std::shared_ptr<spic::GameObject>> entities;

void InitGame() {
	spic::GameEngine* engine = spic::GameEngine::GetInstance();
	std::shared_ptr<spic::extensions::Box2DExtension> physicsExtension = std::make_shared<spic::extensions::Box2DExtension>();
	engine->AddExtension(std::move(physicsExtension));

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

	std::shared_ptr<spic::GameObject> platform = std::make_shared<spic::GameObject>();
	std::string platformTag = "platform";
	std::shared_ptr<spic::Transform> platformTransform = std::make_shared<spic::Transform>();
	platformTransform->position = { 0.0f,  2.0f };
	platformTransform->rotation = 0.0f;
	platformTransform->scale = 0.0f;
	std::shared_ptr<spic::BoxCollider> platformCollider = std::make_shared<spic::BoxCollider>();
	platformCollider->Width(8.75f);
	platformCollider->Height(0.275f);
	std::shared_ptr<spic::RigidBody> platformRigidBody = std::make_shared<spic::RigidBody>(1.0f, 0.0f, spic::BodyType::staticBody);

	platform->Tag(platformTag);
	platform->Transform(platformTransform);
	platform->AddComponent<spic::BoxCollider>(platformCollider);
	platform->AddComponent<spic::RigidBody>(platformRigidBody);

	entities.emplace_back(box);
	entities.emplace_back(platform);
}

void StartGame() {
	const spic::internal::systems::PhysicsSystem system = spic::internal::systems::PhysicsSystem();
	while (true) {
		system.Update(entities);
		//std::cout << "x: " << box->Transform()->position.x << ", y: " << box->Transform()->position.y << std::endl;
	}
}

int main()
{
	InitGame();
	StartGame();
}