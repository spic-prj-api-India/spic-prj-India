#include "GameStatusSendScript.h"
#include "GameEngine.hpp"
#include <SocketUDPExtension.hpp>

GameStatusSendScript::GameStatusSendScript() : SocketScript(), gameStatus{ GameStatus::PLAYING }
{
	this->AddSocket(spic::GameEngine::GetInstance()->GetExtension<spic::extensions::SocketUDPExtension>());
}

void GameStatusSendScript::Send(std::shared_ptr<spic::GameObject> entity)
{
	if (gameStatus == GameStatus::PLAYING)
		return;

	spic::NetworkPacket networkPacket = spic::NetworkPacket();
	networkPacket.name = this->Parent()->Name();

	if (gameStatus == GameStatus::LOST)
		networkPacket.data["game_status"] = std::to_string(GameStatus::WON);
	if (gameStatus == GameStatus::WON)
		networkPacket.data["game_status"] = std::to_string(GameStatus::LOST);

	networkPacket.typeMessage = spic::MessageType::SYNC;
	SendPacket(networkPacket);

	if (gameStatus == GameStatus::LOST)
		spic::GameEngine::GetInstance()->LoadSceneByName("lost");
	if (gameStatus == GameStatus::WON)
		spic::GameEngine::GetInstance()->LoadSceneByName("won");
}

void GameStatusSendScript::SetGameStatus(GameStatus newGameStatus)
{
	gameStatus = newGameStatus;
}

void GameStatusSendScript::CreateEntity(const spic::NetworkPacket* packet, std::shared_ptr<spic::GameObject> entity)
{
}

void GameStatusSendScript::DestroyEntity(const spic::NetworkPacket* packet, std::shared_ptr<spic::GameObject> entity)
{
}

void GameStatusSendScript::SyncEntity(const spic::NetworkPacket* packet, std::shared_ptr<spic::GameObject> entity)
{
}

void GameStatusSendScript::UpdateEntity(const spic::NetworkPacket* packet, std::shared_ptr<spic::GameObject> entity)
{
}