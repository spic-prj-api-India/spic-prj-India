#include "InputSystem.hpp"
#include "InputManager.hpp"
#include "InputImpl.hpp"
#include "Input.hpp"
#include "Button.hpp"
#include "TypeHelper.hpp"
#include "BehaviourScript.hpp"
#include "IncreaseGameSpeedListener.hpp"
#include "DecreaseGameSpeedListener.hpp"
#include "ResetGameSpeedListener.hpp"
#include "Debug.hpp"
#include "Settings.hpp"

namespace spic::internal::systems 
{
	InputSystem::InputSystem() 
	{
	}

	void InputSystem::Start(std::vector<std::shared_ptr<spic::GameObject>>& entities, Scene& currentScene)
	{
		buttonClickListener = std::make_shared<spic::internal::input::ButtonClickListener>();
		spic::input::Subscribe(spic::settings::MOUSEBUTTON_BOUND_TO_BUTTONS, this->buttonClickListener);

		if (spic::debug::DEBUG_MODE)
		{
			auto increase = std::make_shared<spic::internal::input::IncreaseGameSpeedListener>();
			auto decrease = std::make_shared<spic::internal::input::DecreaseGameSpeedListener>();
			auto reset = std::make_shared<spic::internal::input::ResetGameSpeedListener>();

			spic::input::Subscribe(spic::settings::INCREASE_SPEED, increase);
			spic::input::Subscribe(spic::settings::DECREASE_SPEED, decrease);
			spic::input::Subscribe(spic::settings::RESET_SPEED, reset);
		}

		auto scripts = this->GetAllScripts(entities);
		for (auto& script : scripts)
		{
			script->OnStart();
		}
	}

	void InputSystem::Update(std::vector<std::shared_ptr<spic::GameObject>>& entities, Scene& currentScene)
	{
		buttonClickListener->SetButtons(std::move(GetButtons(entities)));
		auto scripts = this->GetAllScripts(entities);

		while (spic::internal::input::impl::Poll())
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
		using namespace spic::helper_functions::type_helper;
		std::vector<std::shared_ptr<spic::Button>> buttons;
		for (const auto& entity : entities) 
		{
			if (SharedPtrIsOfType<spic::Button>(entity))
				buttons.emplace_back(CastSharedPtrToType<spic::Button>(entity));

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