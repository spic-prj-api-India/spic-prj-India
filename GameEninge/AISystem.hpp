#ifndef AISYSTEM_H_
#define AISYSTEM_H_

#include "ISystem.hpp"
#include "Flock.hpp"

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
		* @brief Initiliazes system
		* @spicapi
		*/
		void Start(std::vector<std::shared_ptr<spic::GameObject>>& entities) override;

		/**
		* @brief Calls Listen method in InputManager
		* @spicapi
		*/
		void Update(std::vector<std::shared_ptr<spic::GameObject>>& entities, Scene& currentScene) override;
	private:
		std::vector<std::shared_ptr<spic::Flock>> GetFlockEntities(std::vector<std::shared_ptr<spic::GameObject>> entities);
	};
}

#endif // AISYSTEM_H_