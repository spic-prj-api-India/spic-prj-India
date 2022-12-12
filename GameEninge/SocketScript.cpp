#include "SocketScript.hpp"
#include <string>
#include "GameEngine.hpp"
#include <map>
#include "EntityManager.hpp"

spic::NetworkPacket spic::SocketScript::PositionPacket(const GameObject* gameobject) const
{
	auto packet = spic::NetworkPacket();
	packet.name = gameobject->Name();
	packet.typeMessage = MessageType::UPDATE;
	packet.data["transform"] = gameobject->Transform()->Serialize().str();
	return packet;
}

void recursion(const std::vector<std::shared_ptr<spic::GameObject>>& objects, const spic::Transform& transOld, const spic::Transform& transNew)
{
	for (auto& object : objects)
	{
		recursion(object->GetChildren(), transOld, transNew);

		auto trans = object->Transform();
		trans->position.x = (trans->position.x - transOld.position.x) + transNew.position.x;
		trans->position.y = (trans->position.y - transOld.position.y) + transNew.position.y;
		trans->rotation = transNew.rotation;
		trans->scale = transNew.scale;
	}
}

void spic::SocketScript::UpdatePosition(const spic::NetworkPacket* packet, GameObject* gameobject) const
{
	auto test = packet->data.find("transform")->second;
	Transform transNew = Transform();
	transNew.Deserialize(test);

	Transform transOld = Transform();
	transOld.Deserialize(gameobject->Transform()->Serialize().str());
	
	recursion(gameobject->GetChildren(), transOld, transNew);
	gameobject->Transform()->Deserialize(test);
}

void spic::SocketScript::RemoveEntity(std::shared_ptr<spic::GameObject> entity)
{
	spic::internal::EntityManager::GetInstance()->RemoveEntity(entity);
}


void spic::SocketScript::SendPacket(const spic::NetworkPacket& packet)
{
	if (auto sock = socket.lock(); sock != nullptr)
	{
		sock->Convert(packet);
	}
}

void spic::SocketScript::RegisterNewEntity(std::shared_ptr<spic::GameObject> entity) const
{
	auto manger = spic::internal::EntityManager::GetInstance();
	manger->AddEntityAlsoToScene(std::move(entity));
}

void spic::SocketScript::AddSocket(std::weak_ptr<spic::extensions::INetworkExtension> socketTypname)
{
	this->socket = std::move(socketTypname);
}

void spic::SocketScript::Retrieve(const spic::NetworkPacket* packet, std::shared_ptr<spic::GameObject> entity)
{
	switch (packet->typeMessage)
	{
		case spic::CREATE:
			this->CreateEntity(packet,entity);
			break;

		case spic::DESTROY:
			this->DestroyEntity(packet, entity);
			break;

		case spic::UPDATE:
			this->UpdateEntity(packet, entity);
			break;
		case spic::SYNC:
			this->SyncEntity(packet, entity);
			break;
		default:
			break;
	}
}