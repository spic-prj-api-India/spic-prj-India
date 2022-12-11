#include "NetworkingRecieveSystem.hpp"
#include "GameEngine.hpp"
#include "SocketScript.hpp"
#include <algorithm>
#include "GeneralHelper.hpp"

spic::internal::systems::NetworkingRecieveSystem::NetworkingRecieveSystem()
{
}

void spic::internal::systems::NetworkingRecieveSystem::Start(std::vector<std::shared_ptr<spic::GameObject>>& entities, Scene& currentScene)
{
	sockets = spic::GameEngine::GetInstance()->GetExtensions<spic::INetworkExtension>();
}


void spic::internal::systems::NetworkingRecieveSystem::Update(std::vector<std::shared_ptr<spic::GameObject>>& entities, Scene& currentScene)
{
	std::vector<spic::NetworkPacket> packets;
	for (auto& socket : sockets)
	{
		auto lock = socket.lock();
		auto temp = lock->RetrieveData();
		packets.insert(packets.end(), temp.begin(), temp.end());
	}

	std::sort(packets.begin(), packets.end(), spic::GeneralHelper::NetworkPacketSorting);
	for (auto& packet : packets)
	{
		auto object = GameObject::Find(packet.name);
		auto components = object->GetComponents<spic::SocketScript>();

		for (auto componet : components)
		{
			componet->Send(object);
		}
	}


}
