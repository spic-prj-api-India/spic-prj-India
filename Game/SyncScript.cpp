#include "SyncScript.h"
#include "GameEngine.hpp"
#include "ShooterSendScript.h"
#include "ShooterReceiveScript.h"
#include "TargetReceiveScript.h"
#include "TargetSendScript.h"
#include "SocketUDPExtension.hpp"
#include "Target.h"
#include "Shooter.h"
#include "GameStatusSendScript.h"
#include "GameStatusReceiveScript.h"

SyncScript::SyncScript() : SocketScript()
{
	this->AddSocket(spic::GameEngine::GetInstance()->GetExtension<spic::extensions::SocketUDPExtension>());
}

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
	if (packet->data.count("isShooter") != 0 && !isTarget && !isShooter) {
		isShooter = true;
		entity->AddComponent<spic::SocketScript>(std::make_shared<ShooterSendScript>());
		entity->AddComponent<spic::SocketScript>(std::make_shared<GameStatusSendScript>());
		auto target = spic::GameObject::Find("Target");
		target->AddComponent<spic::SocketScript>(std::make_shared<TargetReceiveScript>());
		spic::helper_functions::type_helper::CastSharedPtrToType<Shooter>(entity)->SetListener();
	}
	if (packet->data.count("ping") != 0 && !isShooter && !isTarget) {
		isTarget = true;
		spic::NetworkPacket networkPacket = spic::NetworkPacket();
		networkPacket.name = entity->Name();
		networkPacket.data["isShooter"] = "";
		networkPacket.typeMessage = spic::MessageType::SYNC;
		SendPacket(networkPacket);
		entity->AddComponent<spic::SocketScript>(std::make_shared<ShooterReceiveScript>());
		entity->AddComponent<spic::SocketScript>(std::make_shared<GameStatusReceiveScript>());
		auto target = spic::GameObject::Find("Target");
		target->AddComponent<spic::SocketScript>(std::make_shared<TargetSendScript>());
		spic::helper_functions::type_helper::CastSharedPtrToType<Target>(target)->SetListener();
	}
}

void SyncScript::UpdateEntity(const spic::NetworkPacket* packet, std::shared_ptr<spic::GameObject> entity)
{
}