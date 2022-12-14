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

		auto scripts = this->GetAllScripts(entities);
		for (auto& script : scripts)
		{
			script->OnStart();
		}

	}

	void InputSystem::Update(std::vector<std::shared_ptr<spic::GameObject>>& entities, Scene& currentScene)
	{
		buttonClickListener->SetButtons(GetButtons(entities));
		auto scripts = this->GetAllScripts(entities);

		while (InputImpl::Poll()) 
		{
			InputManager::GetInstance()->Listen();

			for (auto& script : currentScene.Camera().GetComponents<spic::BehaviourScript>()) {
				script->OnInput();
			}
			
			for (auto& script : scripts)
			{
				script->OnInput();
			}
		}

		for (auto& script : scripts)
		{
			script->OnUpdate();
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
	std::vector<std::shared_ptr<spic::BehaviourScript>> InputSystem::GetAllScripts(std::vector<std::shared_ptr<spic::GameObject>>& entities)
	{
		std::vector<std::shared_ptr<spic::BehaviourScript>> scripts;

		for (auto& entity : entities) 
		{
			for (const auto& script : entity->GetComponents<spic::BehaviourScript>()) 
				scripts.emplace_back(script);
			

			auto children = entity->GetChildren();
			auto childrenScripts = GetAllScripts(children);

			std::copy(childrenScripts.begin(), childrenScripts.end(), std::back_inserter(scripts));
		}
		return scripts;
	}
}