// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// Use to remove SDL2 warnings from error list
#include <codeanalysis\warnings.h>
#pragma warning( push )
#pragma warning ( disable : ALL_CODE_ANALYSIS_WARNINGS )
#include "SDL2/SDL.h"
#pragma warning( pop )
#include <iostream>
#include "GameEngine.hpp"
#include <PhysicsSystem.hpp>
#include <BoxCollider.hpp>
#include <PhysicsExtension1.hpp>
#include "CollisionDetectionScript.h"
#include <ScriptSystem.hpp>
#include <InputSystem.hpp>
#include <Input.hpp>
#include "MouseListener.h"
#include "KeyListener.h"
#include "EntityManager.hpp"
#undef main

std::shared_ptr<spic::Scene> scene;

void InitGame() {
	// Init
	spic::GameEngine* engine = spic::GameEngine::GetInstance();
	scene = std::make_shared<spic::Scene>();

	// Physics test
	std::shared_ptr<spic::extensions::PhysicsExtension1> physicsExtension = std::make_shared<spic::extensions::PhysicsExtension1>();
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

	scene->AddContent(box);
	scene->AddContent(platform);

	// Input test
	std::shared_ptr<MouseListener> mouseListener = std::make_shared<MouseListener>();
	std::shared_ptr<KeyListener> keyListener = std::make_shared<KeyListener>();
	spic::Input::Subscribe(spic::Input::MouseButton::LEFT, mouseListener);
	spic::Input::Subscribe(spic::Input::KeyCode::A, keyListener);
}

void StartGame() {
	// Start
	spic::GameEngine* engine = spic::GameEngine::GetInstance();
	engine->LoadScene(scene);
	engine->Start();
}

int main()
{
	InitGame();
	StartGame();
}