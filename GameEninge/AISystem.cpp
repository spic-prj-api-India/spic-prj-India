#include "AISystem.hpp"
#include "TypeHelper.hpp"

namespace spic::internal::systems {
	AISystem::AISystem()
	{
	}

	void AISystem::Start(std::vector<std::shared_ptr<spic::GameObject>>& entities, Scene& currentScene)
	{
	}

	void AISystem::Update(std::vector<std::shared_ptr<spic::GameObject>>& entities, Scene& currentScene)
	{
		std::vector<std::shared_ptr<spic::ForceDriven>> forceDrivenEntities;
		GetForceDrivenEntities(forceDrivenEntities, entities);
		for (const auto& forceDrivenEntity : forceDrivenEntities) 
		{
			forceDrivenEntity->UpdateForceDrivenEntity(forceDrivenEntities);
		}
	}

	void AISystem::GetForceDrivenEntities(std::vector<std::shared_ptr<spic::ForceDriven>>& forceDrivenEntities, 
		const std::vector<std::shared_ptr<spic::GameObject>>& entities)
	{
		for (const auto& entity : entities) 
		{
			if (spic::helper_functions::type_helper::SharedPtrIsOfType<spic::ForceDriven>(entity))
				forceDrivenEntities.emplace_back(spic::helper_functions::type_helper::CastSharedPtrToType<spic::ForceDriven>(entity));

			GetForceDrivenEntities(forceDrivenEntities, entity->GetChildren());
		}
	}
}