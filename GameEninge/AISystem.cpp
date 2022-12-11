#include "AISystem.hpp"
#include "TypeHelper.hpp"

namespace spic::internal::systems {
	AISystem::AISystem()
	{}

	void AISystem::Start(std::vector<std::shared_ptr<spic::GameObject>>& entities, Scene& currentScene)
	{}

	void AISystem::Update(std::vector<std::shared_ptr<spic::GameObject>>& entities, Scene& currentScene)
	{
		std::vector<std::shared_ptr<spic::Flock>> flocks = GetFlockEntities(entities);
		for (const auto& flock : flocks) {
			flock->UpdateFlock(flocks);
		}
	}

	std::vector<std::shared_ptr<spic::Flock>> AISystem::GetFlockEntities(std::vector<std::shared_ptr<spic::GameObject>> entities)
	{
		// Todo recursion flock entities adden
		std::vector<std::shared_ptr<spic::Flock>> flockEntities;
		for (const auto& entity : entities) {
			if (spic::TypeHelper::SharedPtrIsOfType<spic::Flock>(entity))
				flockEntities.emplace_back(spic::TypeHelper::CastSharedPtrToType<spic::Flock>(entity));
			for (const auto& child : entity->GetChildren()) {
				if (spic::TypeHelper::SharedPtrIsOfType<spic::Flock>(child))
					flockEntities.emplace_back(spic::TypeHelper::CastSharedPtrToType<spic::Flock>(child));
			}
		}
		return flockEntities;
	}


}