#include "ShooterSendScript.h"
#include "GameEngine.hpp"
#include <SocketUDPExtension.hpp>

ShooterSendScript::ShooterSendScript() : SocketScript()
{
	this->AddSocket(spic::GameEngine::GetInstance()->GetExtension<spic::extensions::SocketUDPExtension>());
}

void ShooterSendScript::SendWin()
{
	spic::NetworkPacket networkPacket = spic::NetworkPacket();
	networkPacket.name = this->Parent()->Name();
	networkPacket.data["won"] = std::to_string(true);
	networkPacket.typeMessage = spic::MessageType::SYNC;
	SendPacket(networkPacket);
}

void ShooterSendScript::Send(std::shared_ptr<spic::GameObject> entity)
{
	spic::NetworkPacket networkPacket = spic::NetworkPacket();
	networkPacket.name = entity->Name();
	networkPacket.data["rotation"] = std::to_string(entity->Transform()->rotation);
	networkPacket.typeMessage = spic::MessageType::UPDATE;
	SendPacket(networkPacket);
}

void ShooterSendScript::CreateEntity(const spic::NetworkPacket* packet, std::shared_ptr<spic::GameObject> entity)
{
}

void ShooterSendScript::DestroyEntity(const spic::NetworkPacket* packet, std::shared_ptr<spic::GameObject> entity)
{
}

void ShooterSendScript::SyncEntity(const spic::NetworkPacket* packet, std::shared_ptr<spic::GameObject> entity)
{
}

void ShooterSendScript::UpdateEntity(const spic::NetworkPacket* packet, std::shared_ptr<spic::GameObject> entity)
{
}