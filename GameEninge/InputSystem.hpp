#ifndef INPUTSYSTEM_H_
#define INPUTSYSTEM_H_

#include "ISystem.hpp"

/**
* @brief A system that calls the Start and Update method in scripts of entities
*/
namespace spic::internal::systems {
	class InputSystem :
		public spic::systems::ISystem
	{
	public:
		InputSystem();

		/**
		* @brief Calls Listen method in InputManager
		* @spicapi
		*/
		virtual void Update(std::vector<std::shared_ptr<spic::GameObject>>& entities, Scene& currentScene) override;
	};
}

#endif // INPUTSYSTEM_H_