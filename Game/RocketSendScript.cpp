#include "RocketSendScript.h"
#include "GameEngine.hpp"
#include <SocketUDPExtension.hpp>

RocketSendScript::RocketSendScript() : SocketScript()
{
	this->AddSocket(spic::GameEngine::GetInstance()->GetExtension<spic::extensions::SocketUDPExtension>());
}

void RocketSendScript::Send(std::shared_ptr<spic::GameObject> entity)
{
	spic::NetworkPacket networkPacket = PositionPacket(entity.get());
	networkPacket.typeMessage = spic::MessageType::UPDATE;
	SendPacket(networkPacket);
	networkPacket.typeMessage = spic::MessageType::CREATE;
	networkPacket.data["rocket_name"] = entity->Name();
	SendPacket(networkPacket);
}

void RocketSendScript::Destroy(DestroyType type)
{
	spic::NetworkPacket networkDestroyPacket = spic::NetworkPacket();
	networkDestroyPacket.name = this->gameObject->Name();
	networkDestroyPacket.data["destroy_type"] = std::to_string(type);
	networkDestroyPacket.typeMessage = spic::MessageType::DESTROY;
	SendPacket(networkDestroyPacket);
}

void RocketSendScript::CreateEntity(const spic::NetworkPacket* packet, std::shared_ptr<spic::GameObject> entity)
{
}

void RocketSendScript::DestroyEntity(const spic::NetworkPacket* packet, std::shared_ptr<spic::GameObject> entity)
{
}

void RocketSendScript::SyncEntity(const spic::NetworkPacket* packet, std::shared_ptr<spic::GameObject> entity)
{
}

void RocketSendScript::UpdateEntity(const spic::NetworkPacket* packet, std::shared_ptr<spic::GameObject> entity)
{
}