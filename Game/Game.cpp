// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "GameEngine.hpp"
#include <PhysicsExtension1.hpp>
#include "MouseListener.h"
#include "KeyListener.h"
#include "Scene.hpp"
#include "MenuScene.h"
#include "GameScene.h"
#include <Input.hpp>

std::shared_ptr<spic::Scene> scene;

void InitGame() {
	// Physics test
	spic::GameEngine* engine = spic::GameEngine::GetInstance();
	std::shared_ptr<spic::extensions::PhysicsExtension1> physicsExtension = std::make_shared<spic::extensions::PhysicsExtension1>();
	engine->AddExtension(std::move(physicsExtension));

	engine->RegisterScene("menu", std::make_shared<MenuScene>());
	engine->RegisterScene("game", std::make_shared<GameScene>());

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
	engine->SetActiveScene("game");
	engine->Start(&values);
}

int main()
{
	InitGame();
	StartGame();
}