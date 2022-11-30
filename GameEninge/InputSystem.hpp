#ifndef INPUTSYSTEM_H_
#define INPUTSYSTEM_H_

#include "ISystem.hpp"
#include "ButtonClickListener.hpp"

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
		* @brief Initiliazes system
		* @spicapi
		*/
		void Start(std::vector<std::shared_ptr<spic::GameObject>>& entities, Scene& currentScene) override;

		/**
		* @brief Calls Listen method in InputManager
		* @spicapi
		*/
		void Update(std::vector<std::shared_ptr<spic::GameObject>>& entities, Scene& currentScene) override;

		std::vector<std::shared_ptr<spic::Button>> GetButtons(std::vector<std::shared_ptr<spic::GameObject>>& entities);

		bool IsButton(const std::shared_ptr<spic::GameObject>& entity);
	private:
		std::shared_ptr<ButtonClickListener> buttonClickListener;
	};
}

#endif // INPUTSYSTEM_H_