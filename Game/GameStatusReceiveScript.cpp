#include "GameStatusReceiveScript.h"
#include "GameStatusSendScript.h"
#include "GameEngine.hpp"
#include <SocketUDPExtension.hpp>

GameStatusReceiveScript::GameStatusReceiveScript() : SocketScript()
{
	this->AddSocket(spic::GameEngine::GetInstance()->GetExtension<spic::extensions::SocketUDPExtension>());
}

void GameStatusReceiveScript::Send(std::shared_ptr<spic::GameObject> entity)
{
}

void GameStatusReceiveScript::CreateEntity(const spic::NetworkPacket* packet, std::shared_ptr<spic::GameObject> entity)
{
}

void GameStatusReceiveScript::DestroyEntity(const spic::NetworkPacket* packet, std::shared_ptr<spic::GameObject> entity)
{
}

void GameStatusReceiveScript::SyncEntity(const spic::NetworkPacket* packet, std::shared_ptr<spic::GameObject> entity)
{
	if (packet->data.count("game_status") == 0)
		return;

	int gameStatus = std::stoi(packet->data.at("game_status"));
	if(gameStatus == GameStatus::LOST)
		spic::GameEngine::GetInstance()->LoadSceneByName("lost");
	else
		spic::GameEngine::GetInstance()->LoadSceneByName("won");
}

void GameStatusReceiveScript::UpdateEntity(const spic::NetworkPacket* packet, std::shared_ptr<spic::GameObject> entity)
{
}