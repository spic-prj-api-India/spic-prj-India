#ifndef AISYSTEM_H_
#define AISYSTEM_H_

#include "ISystem.hpp"
#include "ForceDriven.hpp"
#include "Obstacle.hpp"

/**
* @brief A system that calls the Start and Update method in scripts of entities
*/
namespace spic::internal::systems {
	class AISystem :
		public spic::systems::ISystem
	{
	public:
		AISystem();

		/**
		* @brief Initiliazes system.
		* @spicapi
		*/
		void Start(std::vector<std::shared_ptr<spic::GameObject>>& entities, Scene& currentScene) override;

		/**
		* @brief Updates force driven entities.
		* @spicapi
		*/
		void Update(std::vector<std::shared_ptr<spic::GameObject>>& entities, Scene& currentScene) override;
	private:
		/**
		* @brief Filters all Force driven entities and obstacles from entities list recursively.
		* @spicapi
		*/
		void FilterEntities(std::vector<std::shared_ptr<spic::ForceDriven>>& forceDrivenEntities, 
			std::vector<std::shared_ptr<spic::GameObject>>& obstacles,
			const std::vector<std::shared_ptr<spic::GameObject>>& entities);
	};
}

#endif // AISYSTEM_H_