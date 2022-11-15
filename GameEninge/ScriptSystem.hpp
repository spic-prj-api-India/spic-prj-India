#ifndef SCRIPTSYSTEM_H_
#define SCRIPTSYSTEM_H_

#include "ISystem.hpp"

/**
* @brief A system that calls the Start and Update method in scripts of entities
*/
namespace spic::internal::systems {
	class ScriptSystem :
		public spic::systems::ISystem
	{
	public:
		ScriptSystem();

		/**
		* @brief Calls Start method in scripts of entities
		* @spicapi
		*/
		void Start(std::vector < std::shared_ptr<spic::GameObject>>& entities) const;

		/**
		* @brief Calls Update method in scripts of entities
		* @spicapi
		*/
		virtual void Update(std::vector<std::shared_ptr<spic::GameObject>>& entities) override;
	};
}

#endif // SCRIPTSYSTEM_H_