#include "ShooterReceiveScript.h"
#include "GameEngine.hpp"
#include <SocketUDPExtension.hpp>
#include "Rocket.h"
#include "RocketReceiveScript.h"
#include "CollisionDetectionScript.h"

ShooterReceiveScript::ShooterReceiveScript() : SocketScript(), sceneLoaded{false}
{
	this->AddSocket(spic::GameEngine::GetInstance()->GetExtension<spic::extensions::SocketUDPExtension>());
}

void ShooterReceiveScript::Send(std::shared_ptr<spic::GameObject> entity)
{
}

void ShooterReceiveScript::CreateEntity(const spic::NetworkPacket* packet, std::shared_ptr<spic::GameObject> entity)
{
	if (packet->data.count("rocket_name") == 0
		|| packet->data.count("transform") == 0)
		return;

	const std::string& rocketName = packet->data.at("rocket_name");
	auto rocket = spic::GameObject::Find(rocketName);
	if (rocket != nullptr)
		return;
	rocket = std::make_shared<Rocket>(rocketName);
	rocket->Transform()->Deserialize(packet->data.at("transform"));
	rocket->AddComponent<spic::SocketScript>(std::make_shared<RocketReceiveScript>());
	spic::GameObject::Create(rocket);
}

void ShooterReceiveScript::DestroyEntity(const spic::NetworkPacket* packet, std::shared_ptr<spic::GameObject> entity)
{
}

void ShooterReceiveScript::SyncEntity(const spic::NetworkPacket* packet, std::shared_ptr<spic::GameObject> entity)
{
	if (packet->data.count("won") == 0 || sceneLoaded)
		return;
	bool won = std::stoi(packet->data.at("won"));
	if(won)
		spic::GameEngine::GetInstance()->LoadSceneByName("won");
	else
		spic::GameEngine::GetInstance()->LoadSceneByName("lost");
}

void ShooterReceiveScript::UpdateEntity(const spic::NetworkPacket* packet, std::shared_ptr<spic::GameObject> entity)
{
	if (packet->data.count("rotation") != 0)
		entity->Transform()->rotation = std::stof(packet->data.at("rotation"));
}