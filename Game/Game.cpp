// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

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
#include "Scene.hpp"
#include <Renderer.hpp>
#include "Color.hpp"

std::shared_ptr<spic::Scene> scene;

void InitGame() {
	// Init
	spic::GameEngine* engine = spic::GameEngine::GetInstance();
	std::unique_ptr<spic::Camera> camera = std::make_unique<spic::Camera>();
	camera->Transform(std::make_shared<spic::Transform>(spic::Point(0.0f, 0.0f), 0.0f, 1.0f));
	camera->BackgroundColor(spic::Color::blue());
	scene = std::make_shared<spic::Scene>(std::move(camera));

	// Physics test
	std::shared_ptr<spic::extensions::PhysicsExtension1> physicsExtension = std::make_shared<spic::extensions::PhysicsExtension1>();
	engine->AddExtension(std::move(physicsExtension));

	std::shared_ptr<spic::GameObject> box = std::make_shared<spic::GameObject>();
	std::string boxName = "box";
	std::shared_ptr<spic::Transform> boxTransform = std::make_shared<spic::Transform>();
	boxTransform->position = { 25.0f, 24.0f };
	boxTransform->rotation = 0.785f;
	boxTransform->scale = 5.0f;
	std::shared_ptr<spic::BoxCollider> boxCollider = std::make_shared<spic::BoxCollider>();
	boxCollider->Width(1.0f);
	boxCollider->Height(1.0f);
	std::shared_ptr<spic::RigidBody> boxRigidBody = std::make_shared<spic::RigidBody>(1.0f, 0.2f, spic::BodyType::dynamicBody);
	std::shared_ptr<CollisionDetectionScript> script = std::make_shared<CollisionDetectionScript>();
	auto boxSprite = std::make_shared<spic::Sprite>("assets/textures/box.png", 1);

	box->Name(boxName);
	box->Transform(boxTransform);
	box->AddComponent<spic::BoxCollider>(boxCollider);
	box->AddComponent<spic::RigidBody>(boxRigidBody);
	box->AddComponent<spic::BehaviourScript>(script);
	box->AddComponent<spic::Sprite>(boxSprite);

	scene->AddContent(box);
	scene->LoadTileMap("assets/maps/Map.tmx", 3);

	// Input test
	std::shared_ptr<MouseListener> mouseListener = std::make_shared<MouseListener>();
	std::shared_ptr<KeyListener> keyListener = std::make_shared<KeyListener>();
	spic::Input::Subscribe(spic::Input::MouseButton::LEFT, mouseListener);
	spic::Input::Subscribe(spic::Input::KeyCode::A, keyListener);
}

void StartGame()
{

	/** Code to show working (remove 2 slashes to get it working)
	 auto transform1 = std::make_shared<spic::Transform>(spic::Point{80.0f,80.0f }, 10.0f,0.5f);
	 auto sprite = std::make_shared<spic::Sprite>("assets/textures/post-apocalyptic-backgrounds/Postapocalypce1/Bright/clouds1.png", spic::Color::magenta(), false, false,0,0);


	 auto transform2 = spic::Transform{ spic::Point{0,0}, 0.5,1.0f };
	 auto sprite1 = std::make_shared<spic::Sprite>("assets/textures/animated-explosion/Explosion_9/Explosion_1.png", spic::Color::white(), false, false,0,1);
	 auto sprite2 = std::make_shared<spic::Sprite>("assets/textures/animated-explosion/Explosion_9/Explosion_2.png", spic::Color::white(), false, false,0,2);
	 auto sprite3 = std::make_shared<spic::Sprite>("assets/textures/animated-explosion/Explosion_9/Explosion_3.png", spic::Color::white(), false, false,0,3);
	 auto sprite4 = std::make_shared<spic::Sprite>("assets/textures/animated-explosion/Explosion_9/Explosion_4.png", spic::Color::white(), false, false,0,4);
	 auto sprite5 = std::make_shared<spic::Sprite>("assets/textures/animated-explosion/Explosion_9/Explosion_5.png", spic::Color::white(), false, false,0,5);
	 auto sprite6 = std::make_shared<spic::Sprite>("assets/textures/animated-explosion/Explosion_9/Explosion_6.png", spic::Color::white(), false, false,0,6);
	 auto sprite7 = std::make_shared<spic::Sprite>("assets/textures/animated-explosion/Explosion_9/Explosion_7.png", spic::Color::white(), false, false,0,7);
	 auto sprite8 = std::make_shared<spic::Sprite>("assets/textures/animated-explosion/Explosion_9/Explosion_8.png", spic::Color::white(), false, false,0,8);
	 auto sprite9 = std::make_shared<spic::Sprite>("assets/textures/animated-explosion/Explosion_9/Explosion_9.png", spic::Color::white(), false, false,0,9);
	 auto sprite10 = std::make_shared<spic::Sprite>("assets/textures/animated-explosion/Explosion_9/Explosion_10.png", spic::Color::white(), false, false,0,10);

	 auto animator = std::make_shared<spic::Animator>(50);
	 animator->AddSprite(std::move(sprite1));
	 animator->AddSprite(std::move(sprite2));
	 animator->AddSprite(std::move(sprite3));
	 animator->AddSprite(std::move(sprite4));
	 animator->AddSprite(std::move(sprite5));
	 animator->AddSprite(std::move(sprite6));
	 animator->AddSprite(std::move(sprite7));
	 animator->AddSprite(std::move(sprite8));
	 animator->AddSprite(std::move(sprite9));
	 animator->AddSprite(std::move(sprite10));



	 auto text = std::make_shared<spic::Text>("test"
		 , "assets/fonts/07558_CenturyGothic.ttf"
		 , 20
		 , spic::Alignment::left
		 , spic::Color::white());

	 text->Width(50);
	 text->Height(50);

	 text->Transform(std::make_shared<spic::Transform>(spic::Point{ 10,0 }, 0.5, 2.0f));

	 auto gameObjectTest = spic::GameObject();

	 gameObjectTest.AddComponent(animator);
	 gameObjectTest.AddComponent(sprite);
	 gameObjectTest.Transform(transform1);
	 gameObjectTest.AddChild(text);

	 **/

	 //while (true)
	 //{
		// spic::internal::Rendering::Clean();
		// //spic::internal::Rendering::DrawSprite(&transform1, &sprite);
		// //spic::internal::Rendering::DrawAnimator(&transform2,animator.get());
		// //spic::internal::Rendering::DrawText(&text);
		// spic::internal::Rendering::Draw(&gameObjectTest);
		// spic::internal::Rendering::Render();
	 //}

	   // Start code gameEngine
	auto values = spic::window::WindowValues{ "Forts 2", 1200, 800, false, spic::window::FULLSCREENTYPE::WINDOWED };
	spic::GameEngine* engine = spic::GameEngine::GetInstance();
	engine->LoadScene(scene);
	engine->Start(&values);
}

int main()
{
	InitGame();
	StartGame();
}