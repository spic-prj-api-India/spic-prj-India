// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "GameEngine.hpp"
#include <PhysicsSystem.hpp>
#include <BoxCollider.hpp>
#include <Box2DExtension.hpp>
#include "CollisionDetectionScript.h"
#include <ScriptSystem.hpp>
#include <InputSystem.hpp>
#include <Input.hpp>
#include "MouseListener.h"
#include "SDL2/SDL.h"
#include "KeyListener.h"
#undef main

std::vector< std::shared_ptr<spic::GameObject>> entities;

void InitGame() {
	spic::GameEngine* engine = spic::GameEngine::GetInstance();
	// Physics test
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

	// Input test
	std::shared_ptr<MouseListener> mouseListener = std::make_shared<MouseListener>();
	std::shared_ptr<KeyListener> keyListener = std::make_shared<KeyListener>();
	spic::Input::Subscribe(spic::Input::MouseButton::LEFT, mouseListener);
	spic::Input::Subscribe(spic::Input::KeyCode::A, keyListener);
}

void StartGame() {
	// Systems
	spic::internal::systems::InputSystem inputSystem = spic::internal::systems::InputSystem();
	spic::internal::systems::PhysicsSystem physicsSystem = spic::internal::systems::PhysicsSystem();
  spic::internal::systems::ScriptSystem scriptSystem = spic::internal::systems::ScriptSystem();
	scriptSystem.Start(entities);

	// Window
	SDL_Window* window = SDL_CreateWindow("window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 500, SDL_WINDOW_RESIZABLE);

	while (true) {
		//physicsSystem.Update(entities);
		inputSystem.Update(entities);
    scriptSystem.Update(entities);
		//std::cout << "x: " << box->Transform()->position.x << ", y: " << box->Transform()->position.y << std::endl;
	}

	SDL_DestroyWindow(window);
	SDL_Quit();
}

int main()
{
	InitGame();
	StartGame();
}