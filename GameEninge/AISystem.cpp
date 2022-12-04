#include "AISystem.hpp"
#include "TypeHelper.hpp"
#include "Pathfinding.hpp"

namespace spic::internal::systems {
	AISystem::AISystem()
	{}

	void AISystem::Start(std::vector<std::shared_ptr<spic::GameObject>>& entities)
	{}

	void AISystem::Update(std::vector<std::shared_ptr<spic::GameObject>>& entities, Scene& currentScene)
	{
		for (const auto& entity : entities) {
			if (entity->HasComponent<Pathfinding>())
				entity->GetComponent<Pathfinding>()->Update();
			for (const auto& child : entity->GetChildren()) {
				if (child->HasComponent<Pathfinding>())
					child->GetComponent<Pathfinding>()->Update();
			}
		}
	}
}