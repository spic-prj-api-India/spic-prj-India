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
	
	void StartRecusion(std::vector<std::shared_ptr<spic::GameObject>> entities)
	{
		for (auto& entity : entities) {
			for (const auto& script : entity->GetComponents<spic::BehaviourScript>()) {
				script->GameObject(entity);
				script->OnStart();
				StartRecusion(std::move(entity->GetChildren()));
			}
		}
	}

	void InputSystem::Start(std::vector<std::shared_ptr<spic::GameObject>>& entities, Scene& currentScene)
	{
		buttonClickListener = std::make_shared<ButtonClickListener>();
		Input::Subscribe(spic::Input::MouseButton::LEFT, buttonClickListener);

		for (const auto& script : currentScene.Camera().GetComponents<spic::BehaviourScript>()) {
			script->GameObject(std::make_shared<GameObject>(currentScene.Camera()));
			script->OnStart();
		}
		StartRecusion(entities);
	}

	void UpdateRecusion(std::vector<std::shared_ptr<spic::GameObject>> entities)
	{
		for (auto& entity : entities) {
			for (const auto& script : entity->GetComponents<spic::BehaviourScript>()) {
				script->OnUpdate();
			}
			UpdateRecusion(std::move(entity->GetChildren()));
		}
		
	}

	void InputSystem::Update(std::vector<std::shared_ptr<spic::GameObject>>& entities, Scene& currentScene)
	{
		buttonClickListener->SetButtons(GetButtons(entities));
		while (InputImpl::Poll()) 
		{
			InputManager::GetInstance()->Listen();
		}

		for (const auto& script : currentScene.Camera().GetComponents<spic::BehaviourScript>()) {
			script->OnUpdate();
		}
		for (auto& entity : entities) {
			for (const auto& script : entity->GetComponents<spic::BehaviourScript>()) {
				script->OnUpdate();
			}
			UpdateRecusion(entity->GetChildren());
		}
	}

	std::vector<std::shared_ptr<spic::Button>> InputSystem::GetButtons(std::vector<std::shared_ptr<spic::GameObject>>& entities)
	{
		std::vector<std::shared_ptr<spic::Button>> buttons;
		for (const auto& entity : entities) 
		{
			if (spic::TypeHelper::SharedPtrIsOfType<spic::Button>(entity))
				buttons.emplace_back(TypeHelper::CastSharedPtrToType<spic::Button>(entity));

			auto childeren = entity->GetChildren();
			auto temp = this->GetButtons(childeren);

			std::copy(temp.begin(), temp.end(), std::back_inserter(buttons));
		}

		return buttons;
	}
}