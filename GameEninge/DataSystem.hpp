#ifndef DATASYSTEM_H_
#define DATASYSTEM_H_

#include "ISystem.hpp"
#include "Persistable.hpp"

/**
* @brief A system that calls the Start and Update method in scripts of entities
*/
namespace spic::internal::systems {
	class DataSystem :
		public spic::systems::ISystem
	{
	public:
		DataSystem();

		/**
		* @brief Loads data in game object
		* @spicapi
		*/
		void Start(std::vector<std::shared_ptr<spic::GameObject>>& entities) override;

		/**
		* @brief Saves data in game object
		* @spicapi
		*/
		void Update(std::vector<std::shared_ptr<spic::GameObject>>& entities, Scene& currentScene) override;
	private:
		/**
	    * @brief Filters all physics entities from entity list
	    * @spicapi
	    */
		std::vector<std::shared_ptr<spic::Persistable>> GetPersistableEntities(const std::vector<std::shared_ptr<spic::GameObject>>& entities) const;
	};
}

#endif // DATASYSTEM_H_