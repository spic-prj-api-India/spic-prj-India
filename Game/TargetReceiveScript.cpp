#include "TargetReceiveScript.h"
#include "GameEngine.hpp"
#include <SocketUDPExtension.hpp>

TargetReceiveScript::TargetReceiveScript() : SocketScript()
{
	this->AddSocket(spic::GameEngine::GetInstance()->GetExtension<spic::extensions::SocketUDPExtension>());
}

void TargetReceiveScript::Send(std::shared_ptr<spic::GameObject> entity)
{
}

void TargetReceiveScript::CreateEntity(const spic::NetworkPacket* packet, std::shared_ptr<spic::GameObject> entity)
{
}

void TargetReceiveScript::DestroyEntity(const spic::NetworkPacket* packet, std::shared_ptr<spic::GameObject> entity)
{
}

void TargetReceiveScript::SyncEntity(const spic::NetworkPacket* packet, std::shared_ptr<spic::GameObject> entity)
{
}

void TargetReceiveScript::UpdateEntity(const spic::NetworkPacket* packet, std::shared_ptr<spic::GameObject> entity)
{
	UpdatePosition(packet, entity.get());
}