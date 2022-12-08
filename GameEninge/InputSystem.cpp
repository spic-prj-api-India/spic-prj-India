#include "InputSystem.hpp"
#include "InputManager.hpp"
#include "InputImpl.hpp"
#include "Input.hpp"
#include "Button.hpp"
#include "TypeHelper.hpp"
#include "BehaviourScript.hpp"

namespace spic::internal::systems {
	InputSystem::InputSystem() 
	{}

	void InputSystem::Start(std::vector<std::shared_ptr<spic::GameObject>>& entities, Scene& currentScene)
	{
		buttonClickListener = std::make_shared<ButtonClickListener>();
		Input::Subscribe(spic::Input::MouseButton::LEFT, buttonClickListener);

		for (const auto& script : currentScene.Camera().GetComponents<spic::BehaviourScript>()) {
			script->GameObject(std::make_shared<GameObject>(currentScene.Camera()));
			script->OnStart();
		}
		for (auto& entity : entities) {
			for (const auto& script : entity->GetComponents<spic::BehaviourScript>()) {
				script->GameObject(entity);
				script->OnStart();
			}
		}
	}

	void InputSystem::Update(std::vector<std::shared_ptr<spic::GameObject>>& entities, Scene& currentScene)
	{
		buttonClickListener->SetButtons(GetButtons(entities));
		while (InputImpl::Poll()) 
		{
			InputManager::GetInstance()->Listen();

			for (const auto& script : currentScene.Camera().GetComponents<spic::BehaviourScript>()) {
				script->OnUpdate();
			}
			for (auto& entity : entities) {
				for (const auto& script : entity->GetComponents<spic::BehaviourScript>()) {
					script->OnUpdate();
				}
			}
		}
	}

	std::vector<std::shared_ptr<spic::Button>> InputSystem::GetButtons(std::vector<std::shared_ptr<spic::GameObject>>& entities)
	{
		std::vector<std::shared_ptr<spic::Button>> buttons;
		for (const auto& entity : entities) {
			if (spic::TypeHelper::SharedPtrIsOfType<spic::Button>(entity))
				buttons.emplace_back(TypeHelper::CastSharedPtrToType<spic::Button>(entity));
			for (const auto& child : entity->GetChildren()) {
				if (spic::TypeHelper::SharedPtrIsOfType<spic::Button>(child))
					buttons.emplace_back(TypeHelper::CastSharedPtrToType<spic::Button>(entity));
			}
		}
		return buttons;
	}
}