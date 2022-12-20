#include "AISystem.hpp"
#include "TypeHelper.hpp"
#include "Steering.hpp"

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
		std::vector<std::shared_ptr<spic::GameObject>> obstacles;

		FilterEntities(forceDrivenEntities, obstacles, entities);
	
		for (const auto& forceDrivenEntity : forceDrivenEntities) {
			const auto& steering = forceDrivenEntity->GetComponent<Steering>();
			if(steering != nullptr)
				steering->SetObstacles(obstacles);
			forceDrivenEntity->UpdateForceDrivenEntity(forceDrivenEntities);
		}
	}

	void AISystem::FilterEntities(std::vector<std::shared_ptr<spic::ForceDriven>>& forceDrivenEntities, 
		std::vector<std::shared_ptr<spic::GameObject>>& obstacles,
		const std::vector<std::shared_ptr<spic::GameObject>>& entities)
	{
		for (const auto& entity : entities) 
		{
			if (spic::helper_functions::type_helper::SharedPtrIsOfType<spic::ForceDriven>(entity))
				forceDrivenEntities.emplace_back(spic::helper_functions::type_helper::CastSharedPtrToType<spic::ForceDriven>(entity));	
			if (spic::helper_functions::type_helper::SharedPtrIsOfType<spic::Obstacle>(entity))
				obstacles.emplace_back(entity);
			FilterEntities(forceDrivenEntities, obstacles, entity->GetChildren());
		}
	}
}