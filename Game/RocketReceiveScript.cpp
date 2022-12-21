#include "RocketReceiveScript.h"
#include "RocketSendScript.h"
#include "GameEngine.hpp"
#include <SocketUDPExtension.hpp>

RocketReceiveScript::RocketReceiveScript() : SocketScript()
{
	this->AddSocket(spic::GameEngine::GetInstance()->GetExtension<spic::extensions::SocketUDPExtension>());
}

void RocketReceiveScript::Send(std::shared_ptr<spic::GameObject> entity)
{
}

void RocketReceiveScript::CreateEntity(const spic::NetworkPacket* packet, std::shared_ptr<spic::GameObject> entity)
{
}

void RocketReceiveScript::DestroyEntity(const spic::NetworkPacket* packet, std::shared_ptr<spic::GameObject> entity)
{
	spic::GameObject::Destroy(entity->Name());
}

void RocketReceiveScript::SyncEntity(const spic::NetworkPacket* packet, std::shared_ptr<spic::GameObject> entity)
{
}

void RocketReceiveScript::UpdateEntity(const spic::NetworkPacket* packet, std::shared_ptr<spic::GameObject> entity)
{
	entity->Transform()->Deserialize(packet->data.at("transform"));
}