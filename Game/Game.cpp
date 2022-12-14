// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "GameEngine.hpp"
#include <PhysicsExtension1.hpp>
#include "MenuScene.h"
#include "PhysicsValues.hpp"
#include "Box.h"
#include "Debug.hpp"
#include "SocketUdpExtension.hpp"
#include <NetworkPacket.hpp>
#include "NetworkingHelper.hpp"

std::shared_ptr<spic::Scene> scene;

void InitGame() {
	spic::GameEngine* engine = spic::GameEngine::GetInstance();
	spic::extensions::PhysicsValues::SCALING_FACTOR = 0.0017f;
	std::shared_ptr<spic::extensions::PhysicsExtension1> physicsExtension = std::make_shared<spic::extensions::PhysicsExtension1>();
	engine->AddExtension(std::move(physicsExtension));

	auto socket = std::make_shared<spic::extensions::SocketUDPExtension>();
	socket->InitListener(13251);

	socket->InitSender(spic::networkingHelper::GetParsedIPConfigData("IPv4 Address"), 13251);
	engine->AddExtension(std::move(socket));

	// Register types
	engine->RegisterType<Box>();

	// Register scenes
	engine->RegisterScene("menu", std::make_shared<MenuScene>());

	spic::Debug::COLLIDER_VISIBILITY = true;
}

void StartGame()
{
	auto values = spic::window::WindowValues{ "Forts 2", 1200, 800, false, spic::window::FULLSCREENTYPE::WINDOWED };
	spic::GameEngine* engine = spic::GameEngine::GetInstance();
	engine->LoadSceneByName("menu");
	engine->Start(&values);
}

int main()
{
	InitGame();
	StartGame();
}