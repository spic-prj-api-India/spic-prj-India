#include "AISystem.hpp"
#include "TypeHelper.hpp"


namespace spic::internal::systems {
	AISystem::AISystem()
	{}

	void AISystem::Start(std::vector<std::shared_ptr<spic::GameObject>>& entities, Scene& currentScene)
	{}

	void AISystem::Update(std::vector<std::shared_ptr<spic::GameObject>>& entities, Scene& currentScene)
	{
		std::vector<std::shared_ptr<spic::ForceDriven>> forceDrivenEntities;
		std::vector<std::shared_ptr<spic::GameObject>> obstacles;

		FilterEntities(forceDrivenEntities, obstacles, entities);
	
		for (const auto& forceDrivenEntity : forceDrivenEntities) {
			forceDrivenEntity->SetObstacles(obstacles);
			forceDrivenEntity->UpdateForceDrivenEntity(forceDrivenEntities);
		}
	}

	void AISystem::FilterEntities(std::vector<std::shared_ptr<spic::ForceDriven>>& forceDrivenEntities, 
		std::vector<std::shared_ptr<spic::GameObject>>& obstacles,
		const std::vector<std::shared_ptr<spic::GameObject>>& entities)
	{
		for (const auto& entity : entities) {
			if (spic::TypeHelper::SharedPtrIsOfType<spic::ForceDriven>(entity))
				forceDrivenEntities.emplace_back(spic::TypeHelper::CastSharedPtrToType<spic::ForceDriven>(entity));	
			if (spic::TypeHelper::SharedPtrIsOfType<spic::Obstacle>(entity))
				obstacles.emplace_back(entity);
			FilterEntities(forceDrivenEntities, obstacles, entity->GetChildren());
		}
	}
}