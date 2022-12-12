#include "NetworkingSendSystem.hpp"
#include "SocketScript.hpp"
#include "GameEngine.hpp"
spic::internal::systems::NetworkingSendSystem::NetworkingSendSystem()
{
}

void spic::internal::systems::NetworkingSendSystem::Start(std::vector<std::shared_ptr<spic::GameObject>>& entities, Scene& currentScene)
{
	sockets = spic::GameEngine::GetInstance()->GetExtensions<spic::extensions::INetworkExtension>();
}

void UpdateRecursion(std::vector<std::shared_ptr<spic::GameObject>>& entities, spic::Scene& currentScene)
{
	for (auto& ent : entities)
	{
		auto children = ent->GetChildren();
		UpdateRecursion(children, currentScene);

		auto components = ent->GetComponents<spic::SocketScript>();

		for (auto componet : components)
		{
			componet->Send(ent);
		}
	}
}

void spic::internal::systems::NetworkingSendSystem::Update(std::vector<std::shared_ptr<spic::GameObject>>& entities, Scene& currentScene)
{
	UpdateRecursion(entities, currentScene);

	for (auto& socketWeak : sockets)
	{
		if (const auto& socket = socketWeak.lock(); socket != nullptr)
		{
			socket->SendData();
		}
	}
}
