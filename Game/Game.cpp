// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "GameEngine.hpp"
#include <PhysicsExtension1.hpp>
#include "MenuScene.h"
#include "BoxPersistable.h"
#include "Debug.hpp"
#include "SocketUdpExtension.hpp"
#include <NetworkPacket.hpp>
#include "NetworkingHelper.hpp"
#include "GameScene.h"
#include "NetworkScene.h"
#include "CreditsScene.h"
#include "MenuScene.h"
#include "CreditsScene.h"
#include "SettingsScene.h"
#include "LoseScene.h"
#include "WinScene.h"
#include "SteeringScene.h"

void InitGame()
{
	// Creates GameEngine instance 
	spic::GameEngine* engine = spic::GameEngine::GetInstance();

	// Creates box2d physics extension and adds it to the extension list
	std::shared_ptr<spic::extensions::PhysicsExtension1> physicsExtension
		= std::make_shared<spic::extensions::PhysicsExtension1>(0.0023f, 4, 2);
	engine->AddExtension(std::move(physicsExtension));

	// Creates a SocketUDPExtension and adds it to the extension list
	const std::string& ownIp = spic::helper_functions::networking_helper::GetParsedIPConfigData("IPv4 Address");
	spic::DataHandler dataHandler = spic::DataHandler("networking");
	std::map<std::string, std::string> networkSettings;
	dataHandler.LoadSettings(networkSettings);
	const std::string& opponentIp = (networkSettings["opponent"]);

	auto socket = std::make_shared<spic::extensions::SocketUDPExtension>();
	socket->InitListener(13252);
	socket->InitSender(opponentIp, 13252);
	engine->AddExtension(std::move(socket));

	// Register object types
	engine->RegisterType<BoxPersistable>();

	// Register scenes
	engine->RegisterScene("menu", std::function<spic::Scene* ()>(MenuScene::Start));
	engine->RegisterScene("game", std::function<spic::Scene* ()>(GameScene::Start));
	engine->RegisterScene("credits", std::function<spic::Scene* ()>(CreditsScene::Start));
	engine->RegisterScene("network", std::function<spic::Scene* ()>(NetworkScene::Start));
	engine->RegisterScene("steering", std::function<spic::Scene* ()>(SteeringScene::Start));
	engine->RegisterScene("won", std::function<spic::Scene* ()>(WinScene::Start));
	engine->RegisterScene("lost", std::function<spic::Scene* ()>(LoseScene::Start));
	engine->RegisterScene("settings", std::function<spic::Scene* ()>(SettingsScene::Start));
}

void StartGame()
{
	spic::settings::COLLIDER_VISIBILITY = false;
	spic::settings::WALL_AVOIDANCE_FEELERS_VISIBILITY = false;
	spic::settings::WINDOW_NAME = "Forts 2";
	spic::settings::WINDOW_WIDTH = 1200;
	spic::settings::WINDOW_HEIGHT = 800;
	spic::GameEngine* engine = spic::GameEngine::GetInstance();
	engine->LoadSceneByName("menu");
	engine->Start();
}

int main()
{
	InitGame();
	StartGame();
}