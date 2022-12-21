#include "TargetSendScript.h"
#include "GameEngine.hpp"
#include <SocketUDPExtension.hpp>

TargetSendScript::TargetSendScript() : SocketScript()
{
	this->AddSocket(spic::GameEngine::GetInstance()->GetExtension<spic::extensions::SocketUDPExtension>());
}

void TargetSendScript::Send(std::shared_ptr<spic::GameObject> entity)
{
	spic::NetworkPacket networkPacket = spic::NetworkPacket();
	networkPacket.name = entity->Name();
	networkPacket.data["transform"] = entity->Transform()->Serialize().str();
	networkPacket.typeMessage = spic::MessageType::UPDATE;
	SendPacket(networkPacket);
}

void TargetSendScript::CreateEntity(const spic::NetworkPacket* packet, std::shared_ptr<spic::GameObject> entity)
{
}

void TargetSendScript::DestroyEntity(const spic::NetworkPacket* packet, std::shared_ptr<spic::GameObject> entity)
{
}

void TargetSendScript::SyncEntity(const spic::NetworkPacket* packet, std::shared_ptr<spic::GameObject> entity)
{
}

void TargetSendScript::UpdateEntity(const spic::NetworkPacket* packet, std::shared_ptr<spic::GameObject> entity)
{
}