#include "InputSystem.hpp"
#include "InputManager.hpp"
#include "InputImpl.hpp"
#include "Input.hpp"
#include "Button.hpp"
#include "TypeHelper.hpp"

namespace spic::internal::systems {
	InputSystem::InputSystem() 
	{}

	void InputSystem::Start(std::vector<std::shared_ptr<spic::GameObject>>& entities, Scene& currentScene)
	{
		buttonClickListener = std::make_shared<ButtonClickListener>();
		Input::Subscribe(spic::Input::MouseButton::LEFT, buttonClickListener);
	}

	void InputSystem::Update(std::vector<std::shared_ptr<spic::GameObject>>& entities, Scene& currentScene)
	{
		buttonClickListener->SetButtons(GetButtons(entities));
		while (InputImpl::Poll()) 
		{
			InputManager::GetInstance()->Listen();
		}
	}

	std::vector<std::shared_ptr<spic::Button>> InputSystem::GetButtons(std::vector<std::shared_ptr<spic::GameObject>>& entities)
	{
		std::vector<std::shared_ptr<spic::Button>> buttons;
		for (const auto& entity : entities) {
			if (IsButton(entity))
				buttons.emplace_back(TypeHelper::CastSharedPtrToType<spic::Button>(entity));
			for (const auto& child : entity->GetChildren()) {
				if (IsButton(child))
					buttons.emplace_back(TypeHelper::CastSharedPtrToType<spic::Button>(entity));
			}
		}
		return buttons;
	}

	bool InputSystem::IsButton(const std::shared_ptr<spic::GameObject>& entity)
	{
		return TypeHelper::SharedPtrIsOfType<spic::Button>(entity);
	}
}