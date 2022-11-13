#include "InputSystem.hpp"
#include "InputManager.hpp"
#include "InputImpl.hpp"

namespace systems {
	InputSystem::InputSystem() {}

	void InputSystem::Update(std::vector<std::shared_ptr<spic::GameObject>> entities) const
	{
		while (InputImpl::Poll()) {
			InputManager::GetInstance()->Listen();
		}
	}
}