#ifndef INPUTSYSTEM_H_
#define INPUTSYSTEM_H_

#include "ISystem.hpp"
#include "ButtonClickListener.hpp"
#include "BehaviourScript.hpp"
/**
* @brief A system that calls the Start and Update method in scripts of entities
*/
namespace spic::internal::systems 
{
	/**
	 * @brief The internal input system
	 * @details This system triggers input behaviour 
	*/
	class InputSystem :
		public spic::systems::ISystem
	{
	public:
		InputSystem();

		/**
		* @brief Initiliazes system
		*/
		void Start(std::vector<std::shared_ptr<spic::GameObject>>& entities, Scene& currentScene) override;

		/**
		* @brief Calls Listen method in InputManager
		*/
		void Update(std::vector<std::shared_ptr<spic::GameObject>>& entities, Scene& currentScene) override;

		/**
		* @brief Filters all Buttons from entities list
		* @param list with Buttons
		*/
		std::vector<std::shared_ptr<spic::Button>> GetButtons(std::vector<std::shared_ptr<spic::GameObject>>& entities);
		std::vector<std::shared_ptr<spic::BehaviourScript>> GetAllScripts(std::vector<std::shared_ptr<spic::GameObject>>& entities);
	private:
		std::shared_ptr<spic::internal::input::ButtonClickListener> buttonClickListener;
	};
}

#endif // INPUTSYSTEM_H_