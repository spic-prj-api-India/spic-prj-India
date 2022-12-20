#include "SyncScript.h"
#include "GameEngine.hpp"
#include "ShooterSendScript.h"
#include "ShooterReceiveScript.h"

void SyncScript::Send(std::shared_ptr<spic::GameObject> entity)
{
	spic::NetworkPacket networkPacket = spic::NetworkPacket();
	networkPacket.name = entity->Name();
	networkPacket.data["ping"] = "";
	networkPacket.typeMessage = spic::MessageType::SYNC;
	SendPacket(networkPacket);
}

void SyncScript::CreateEntity(const spic::NetworkPacket* packet, std::shared_ptr<spic::GameObject> entity)
{
}

void SyncScript::DestroyEntity(const spic::NetworkPacket* packet, std::shared_ptr<spic::GameObject> entity)
{
}

void SyncScript::SyncEntity(const spic::NetworkPacket* packet, std::shared_ptr<spic::GameObject> entity)
{
	if (packet->data.count("ping") != 0 && !isShooter && isTarget) {
		isTarget = true;
		spic::NetworkPacket networkPacket = spic::NetworkPacket();
		networkPacket.name = entity->Name();
		networkPacket.data["isShooter"] = "";
		networkPacket.typeMessage = spic::MessageType::SYNC;
		SendPacket(networkPacket);
		entity->AddComponent<spic::SocketScript>(std::make_shared<ShooterReceiveScript>());
		auto target = spic::GameObject::Find("target");
		//target->AddComponent<spic::SocketScript>(std::make_shared<TargetSendScript>())
	}
	if (packet->data.count("isShooter") && !isTarget && isShooter) {
		isShooter = true;
		entity->AddComponent<spic::SocketScript>(std::make_shared<ShooterSendScript>());
		auto target = spic::GameObject::Find("target");
		//target->AddComponent<spic::SocketScript>(std::make_shared<TargetReceiveScript>())
	}
}

void SyncScript::UpdateEntity(const spic::NetworkPacket* packet, std::shared_ptr<spic::GameObject> entity)
{
}