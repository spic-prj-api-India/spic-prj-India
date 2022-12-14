#include "ScriptSystem.hpp"
#include "BehaviourScript.hpp"

namespace spic::internal::systems {
	ScriptSystem::ScriptSystem()
	{}

	void StartRecursion(std::vector<std::shared_ptr<spic::GameObject>> entities)
	{
		for (auto& entity : entities) {
			for (const auto& script : entity->GetComponents<spic::BehaviourScript>()) {
				script->OnStart();
			}
			StartRecursion(std::move(entity->GetChildren()));
		}
	}

	void ScriptSystem::Start(std::vector<std::shared_ptr<spic::GameObject>>& entities, Scene& currentScene)
	{
		for (const auto& script : currentScene.Camera().GetComponents<spic::BehaviourScript>()) {
			script->OnStart();
		}
		StartRecursion(entities);
	}

	void UpdateRecursion(std::vector<std::shared_ptr<spic::GameObject>> entities)
	{
		for (auto& entity : entities) {
			for (const auto& script : entity->GetComponents<spic::BehaviourScript>()) {
				script->OnUpdate();
			}
			UpdateRecursion(std::move(entity->GetChildren()));
		}
	}

	void ScriptSystem::Update(std::vector<std::shared_ptr<spic::GameObject>>& entities, Scene& currentScene)
	{
		for (const auto& script : currentScene.Camera().GetComponents<spic::BehaviourScript>()) {
			script->OnUpdate();
		}
		UpdateRecursion(entities);
	}
}