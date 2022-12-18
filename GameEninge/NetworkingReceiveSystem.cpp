#include "NetworkingReceiveSystem.hpp"
#include "GameEngine.hpp"
#include "SocketScript.hpp"
#include <algorithm>
#include "GeneralHelper.hpp"

spic::internal::systems::NetworkingReceiveSystem::NetworkingReceiveSystem()
{
}

void spic::internal::systems::NetworkingReceiveSystem::Start(std::vector<std::shared_ptr<spic::GameObject>>& entities, Scene& currentScene)
{
	sockets = spic::GameEngine::GetInstance()->GetExtensions<spic::extensions::INetworkExtension>();
}


void spic::internal::systems::NetworkingReceiveSystem::Update(std::vector<std::shared_ptr<spic::GameObject>>& entities, Scene& currentScene)
{
	std::vector<spic::NetworkPacket> packets;
	for (auto& socket : sockets)
	{
		auto lock = socket.lock();
		auto temp = lock->RetrieveData();
		packets.insert(packets.end(), temp.begin(), temp.end());
	}

	std::sort(packets.begin(), packets.end(), spic::general_helper::NetworkPacketSorting);
	for (auto& packet : packets)
	{
		auto object = GameObject::Find(packet.name);
		auto components = object->GetComponents<spic::SocketScript>();

		for (auto component : components)
		{
			component->Retrieve(&packet, object);
		}
	}
}