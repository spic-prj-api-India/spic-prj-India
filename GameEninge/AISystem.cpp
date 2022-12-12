#include "AISystem.hpp"
#include "TypeHelper.hpp"

namespace spic::internal::systems {
	AISystem::AISystem()
	{}

	void AISystem::Start(std::vector<std::shared_ptr<spic::GameObject>>& entities, Scene& currentScene)
	{}

	void AISystem::Update(std::vector<std::shared_ptr<spic::GameObject>>& entities, Scene& currentScene)
	{
		std::vector<std::shared_ptr<spic::ForceDriven>> flocks = GetForceDrivenEntities(entities);
		for (const auto& flock : flocks) {
			flock->UpdateForceDrivenEntity(flocks);
		}
	}

	std::vector<std::shared_ptr<spic::ForceDriven>> AISystem::GetForceDrivenEntities(std::vector<std::shared_ptr<spic::GameObject>> entities)
	{
		// Todo recursion flock entities adden
		std::vector<std::shared_ptr<spic::ForceDriven>> flockEntities;
		for (const auto& entity : entities) {
			if (spic::TypeHelper::SharedPtrIsOfType<spic::ForceDriven>(entity))
				flockEntities.emplace_back(spic::TypeHelper::CastSharedPtrToType<spic::ForceDriven>(entity));
			for (const auto& child : entity->GetChildren()) {
				if (spic::TypeHelper::SharedPtrIsOfType<spic::ForceDriven>(child))
					flockEntities.emplace_back(spic::TypeHelper::CastSharedPtrToType<spic::ForceDriven>(child));
			}
		}
		return flockEntities;
	}
}