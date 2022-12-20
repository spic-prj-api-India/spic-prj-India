#include "ShooterReceiveScript.h"
#include "GameEngine.hpp"

void ShooterReceiveScript::Send(std::shared_ptr<spic::GameObject> entity)
{
}

void ShooterReceiveScript::CreateEntity(const spic::NetworkPacket* packet, std::shared_ptr<spic::GameObject> entity)
{
}

void ShooterReceiveScript::DestroyEntity(const spic::NetworkPacket* packet, std::shared_ptr<spic::GameObject> entity)
{
}

void ShooterReceiveScript::SyncEntity(const spic::NetworkPacket* packet, std::shared_ptr<spic::GameObject> entity)
{
}

void ShooterReceiveScript::UpdateEntity(const spic::NetworkPacket* packet, std::shared_ptr<spic::GameObject> entity)
{
	if (packet->data.count("rotation") != 0)
		entity->Transform()->rotation = std::stof(packet->data.at("rotation"));
}