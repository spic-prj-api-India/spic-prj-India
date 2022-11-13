#ifndef INPUTSYSTEM_H_
#define INPUTSYSTEM_H_

#include "ISystem.hpp"

/**
* @brief A system that calls the Start and Update method in scripts of entities
*/
namespace systems {
	class InputSystem :
		public ISystem
	{
	public:
		InputSystem();

		/**
		* @brief Calls Listen method in InputManager
		* @spicapi
		*/
		void Update(std::vector<std::shared_ptr<spic::GameObject>> entities) const;
	};
}

#endif // INPUTSYSTEM_H_