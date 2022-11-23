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
#include <Renderer.hpp>

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

void StartGame() 
{

 ///** Code to show working (remove 2 slashes to get it working)
  auto transform1 = std::make_shared<spic::Transform>(spic::Point{80,80}, 10,0.5);
  auto sprite = std::make_shared<spic::Sprite>("assets/textures/post-apocalyptic-backgrounds/Postapocalypce1/Bright/clouds1.png", spic::Color::magenta(), false, false,0,0);


  auto transform2 = spic::Transform{ spic::Point{0,0}, 0.5,1.0f };
  auto sprite1 = std::make_shared<spic::Sprite>("assets/textures/animated-explosion/Explosion_9/Explosion_1.png", spic::Color::white(), false, false,0,1);
  auto sprite2 = std::make_shared<spic::Sprite>("assets/textures/animated-explosion/Explosion_9/Explosion_2.png", spic::Color::white(), false, false,0,2);
  auto sprite3 = std::make_shared<spic::Sprite>("assets/textures/animated-explosion/Explosion_9/Explosion_3.png", spic::Color::white(), false, false,0,3);
  auto sprite4 = std::make_shared<spic::Sprite>("assets/textures/animated-explosion/Explosion_9/Explosion_4.png", spic::Color::white(), false, false,0,4);
  auto sprite5 = std::make_shared<spic::Sprite>("assets/textures/animated-explosion/Explosion_9/Explosion_5.png", spic::Color::white(), false, false,0,5);
  auto sprite6 = std::make_shared<spic::Sprite>("assets/textures/animated-explosion/Explosion_9/Explosion_6.png", spic::Color::white(), false, false,0,6);
  auto sprite7 = std::make_shared<spic::Sprite>("assets/textures/animated-explosion/PNG/Explosion_9/Explosion_7.png", spic::Color::white(), false, false,0,7);
  auto sprite8 = std::make_shared<spic::Sprite>("assets/textures/animated-explosion/PNG/Explosion_9/Explosion_8.png", spic::Color::white(), false, false,0,8);
  auto sprite9 = std::make_shared<spic::Sprite>("assets/textures/animated-explosion/PNG/Explosion_9/Explosion_9.png", spic::Color::white(), false, false,0,9);
  auto sprite10 = std::make_shared<spic::Sprite>("assets/textures/animated-explosion/PNG/Explosion_9/Explosion_10.png", spic::Color::white(), false, false,0,10);

  auto animator = std::make_shared<spic::Animator>(3);
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


  auto values = spic::window::WindowValues{ "Forts 2", 1200, 800, false, spic::window::WINDOWED };

  spic::internal::Rendering::Start(&values);

  while (true)
  {
	  spic::internal::Rendering::Clean();
	  //spic::internal::Rendering::DrawSprite(&transform1, &sprite);
	  //spic::internal::Rendering::DrawAnimator(&transform2,&animator);
	  //spic::internal::Rendering::DrawText(&text);
	  spic::internal::Rendering::Draw(&gameObjectTest);
	  spic::internal::Rendering::Render();
  }

  
	/** GamEnigne code (remove 2 slashes to get it working)
	// Start code gameEngine
	spic::GameEngine* engine = spic::GameEngine::GetInstance();
	engine->LoadScene(scene);
	engine->Start();
	//*/
}

int main()
{
	


	//InitGame();
	StartGame();
}