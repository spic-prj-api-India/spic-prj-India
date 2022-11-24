#include "InputSystem.hpp"
#include "InputManager.hpp"
#include "InputImpl.hpp"

namespace spic::internal::systems {
	InputSystem::InputSystem() 
	{}

	void InputSystem::Start(std::vector<std::shared_ptr<spic::GameObject>>& entities)
	{}

	void InputSystem::Update(std::vector<std::shared_ptr<spic::GameObject>>& entities, Scene& currentScene)
	{
		while (InputImpl::Poll()) 
		{
			InputManager::GetInstance()->Listen();
		}
	}
}