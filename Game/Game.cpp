// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "GameEngine.hpp"
#include <PhysicsExtension1.hpp>
#include "MenuScene.h"
#include "Box.h"
#include "Debug.hpp"
#include "SocketUdpExtension.hpp"
#include <NetworkPacket.hpp>
#include "NetworkingHelper.hpp"
#include "GameScene.h"
#include "FlockingScene.h"
#include "CreditsScene.h"
#include "MenuScene.h"
#include "CreditsScene.h"
#include "SettingsScene.h"


void InitGame() {

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
	const std::string& opponentIp = (networkSettings["player1"] == ownIp ? networkSettings["player2"] : networkSettings["player1"]);

	auto socket = std::make_shared<spic::extensions::SocketUDPExtension>();
	socket->InitListener(13251);
	socket->InitSender(opponentIp, 13251);
	engine->AddExtension(std::move(socket));

	// Register object types
	engine->RegisterType<Box>();

	// Register scenes
	engine->RegisterScene("menu", std::function<spic::Scene* ()>(MenuScene::Start));
	engine->RegisterScene("game", std::function<spic::Scene* ()>(GameScene::Start));
	engine->RegisterScene("credits", std::function<spic::Scene* ()>(CreditsScene::Start));
	engine->RegisterScene("flock", std::function<spic::Scene* ()>(FlockingScene::Start));
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