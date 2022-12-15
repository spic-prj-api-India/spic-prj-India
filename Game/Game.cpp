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
#include "GameScene.h"
#include "FlockingScene.h"
#include "CredditsScene.h"

std::shared_ptr<spic::Scene> scene;

void InitGame() {
	spic::GameEngine* engine = spic::GameEngine::GetInstance();
	spic::extensions::PhysicsValues::PIX2MET = 0.0023f;
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
	engine->RegisterScene("game", std::make_shared<GameScene>());
	engine->RegisterScene("flock", std::make_shared<FlockingScene>());
	engine->RegisterScene("creddits", std::make_shared<CredditsScene>());

	spic::Debug::COLLIDER_VISIBILITY = true;
}

void StartGame()
{
	spic::window::WINDOW_NAME = "Forts 2";
	spic::window::WINDOW_WIDTH = 1200;
	spic::window::WINDOW_HEIGHT = 800;
	spic::GameEngine* engine = spic::GameEngine::GetInstance();
	engine->LoadSceneByName("menu");
	engine->Start();
}

int main()
{
	InitGame();
	StartGame();
}