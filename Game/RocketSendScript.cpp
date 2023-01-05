#include "RocketSendScript.h"
#include "GameEngine.hpp"
#include <SocketUDPExtension.hpp>

RocketSendScript::RocketSendScript() : SocketScript()
{
	this->AddSocket(spic::GameEngine::GetInstance()->GetExtension<spic::extensions::SocketUDPExtension>());
}

void RocketSendScript::Send(std::shared_ptr<spic::GameObject> entity)
{
	spic::NetworkPacket networkCreatePacket = spic::NetworkPacket();
	const std::string& transformSerialized = entity->Transform()->Serialize().str();
	networkCreatePacket.name = "Shooter";
	networkCreatePacket.typeMessage = spic::MessageType::CREATE;
	networkCreatePacket.data["rocket_name"] = entity->Name();
	networkCreatePacket.data["transform"] = transformSerialized;
	spic::NetworkPacket networkUpdatePacket = spic::NetworkPacket();
	networkUpdatePacket.name = entity->Name();
	networkUpdatePacket.data["transform"] = transformSerialized;
	networkUpdatePacket.typeMessage = spic::MessageType::UPDATE;
	SendPacket(networkCreatePacket);
	SendPacket(networkUpdatePacket);
}

void RocketSendScript::Destroy(DestroyType type)
{
	spic::NetworkPacket networkDestroyPacket = spic::NetworkPacket();
	networkDestroyPacket.name = this->Parent()->Name();
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