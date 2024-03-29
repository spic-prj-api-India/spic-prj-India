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
#include "DifficultyScene.h"
#include "NetworkScene.h"
#include "CreditsScene.h"
#include "MenuScene.h"
#include "CreditsScene.h"
#include "SettingsScene.h"
#include "FlockSettingsScene.h"
#include "SoundSettingsScene.h"
#include "NetworkSettingsScene.h"
#include "LoseScene.h"
#include "WinScene.h"
#include "SteeringScene.h"
#include "SaveScene.h"
#include "GameScene.h"
#include "InstructionsScene.h"
#include "JengaInstructionsScene.h"
#include "RocketGameInstructionsScene.h"
#include "SteeringInstructionsScene.h"
#include "KeyFunctionsScene.h"

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
	spic::DataHandler dataHandler = spic::DataHandler("network_settings");
	std::map<std::string, std::string> networkSettings;
	dataHandler.LoadSettings(networkSettings);
	const std::string& opponentIp = (networkSettings["opponent_ip"]);

	auto socket = std::make_shared<spic::extensions::SocketUDPExtension>();
	socket->InitListener(13251);
	socket->InitSender(opponentIp, 13252);
	engine->AddExtension(std::move(socket));

	// Register object types
	engine->RegisterType<BoxPersistable>();

	// Register scenes
	engine->RegisterScene("menu", std::function<spic::Scene* ()>(MenuScene::Start));
	engine->RegisterScene("jenga-settings", std::function<spic::Scene* ()>(DifficultyScene::Start));
	engine->RegisterScene("jenga", std::function<spic::Scene* ()>(GameScene::Start));
	engine->RegisterScene("jenga-save", std::function<spic::Scene* ()>(SaveScene::Start));
	engine->RegisterScene("credits", std::function<spic::Scene* ()>(CreditsScene::Start));
	engine->RegisterScene("network", std::function<spic::Scene* ()>(NetworkScene::Start));
	engine->RegisterScene("steering", std::function<spic::Scene* ()>(SteeringScene::Start));
	engine->RegisterScene("won", std::function<spic::Scene* ()>(WinScene::Start));
	engine->RegisterScene("lost", std::function<spic::Scene* ()>(LoseScene::Start));
	engine->RegisterScene("settings", std::function<spic::Scene* ()>(SettingsScene::Start));
	engine->RegisterScene("flockSettings", std::function<spic::Scene* ()>(FlockSettingsScene::Start));
	engine->RegisterScene("soundSettings", std::function<spic::Scene* ()>(SoundSettingsScene::Start));
	engine->RegisterScene("networkSettings", std::function<spic::Scene* ()>(NetworkSettingsScene::Start));
	engine->RegisterScene("instructions", std::function<spic::Scene* ()>(InstructionsScene::Start));
	engine->RegisterScene("jenga-instructions", std::function<spic::Scene* ()>(JengaInstructionsScene::Start));
	engine->RegisterScene("rocketgame-instructions", std::function<spic::Scene* ()>(RocketGameInstructionsScene::Start));
	engine->RegisterScene("steering-instructions", std::function<spic::Scene* ()>(SteeringInstructionsScene::Start));
	engine->RegisterScene("key-functions", std::function<spic::Scene* ()>(KeyFunctionsScene::Start));
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