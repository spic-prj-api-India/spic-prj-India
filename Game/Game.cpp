// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "GameEngine.hpp"
#include <PhysicsSystem.hpp>
#include <BoxCollider.hpp>
#include <PhysicsExtension.hpp>
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
	std::shared_ptr<spic::extensions::PhysicsExtension> physicsExtension = std::make_shared<spic::extensions::PhysicsExtension>();
	engine->AddExtension(std::move(physicsExtension));

	std::shared_ptr<spic::GameObject> box = std::make_shared<spic::GameObject>();
	std::string boxTag = "box";
	std::shared_ptr<spic::Transform> boxTransform = std::make_shared<spic::Transform>();
	boxTransform->position = { -2.5f, -2.5f };
	boxTransform->rotation = 45.0f;
	boxTransform->scale = 1.0f;
	std::shared_ptr<spic::BoxCollider> boxCollider = std::make_shared<spic::BoxCollider>();
	boxCollider->Width(0.3f);
	boxCollider->Height(0.3f);
	std::shared_ptr<spic::RigidBody> boxRigidBody = std::make_shared<spic::RigidBody>(1.0f, 0.2f, spic::BodyType::dynamicBody);
	std::shared_ptr<CollisionDetectionScript> script = std::make_shared<CollisionDetectionScript>();

	box->Tag(boxTag);
	box->Transform(boxTransform);
	box->AddComponent<spic::BoxCollider>(boxCollider);
	box->AddComponent<spic::RigidBody>(boxRigidBody);
	box->AddComponent<spic::BehaviourScript>(script);

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
	// Scene
	spic::Scene* scene = new spic::Scene();

	// Systems
	spic::internal::systems::InputSystem inputSystem = spic::internal::systems::InputSystem();
	spic::internal::systems::PhysicsSystem physicsSystem = spic::internal::systems::PhysicsSystem();
	spic::internal::systems::ScriptSystem scriptSystem = spic::internal::systems::ScriptSystem();
	scriptSystem.Start(entities);

	// Window
	SDL_Window* window = SDL_CreateWindow("window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 500, SDL_WINDOW_RESIZABLE);

	while (true) {
		physicsSystem.Update(entities, *scene);
		inputSystem.Update(entities, *scene);
		scriptSystem.Update(entities, *scene);
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