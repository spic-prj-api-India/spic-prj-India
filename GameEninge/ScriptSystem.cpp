#include "ScriptSystem.hpp"
#include "BehaviourScript.hpp"


namespace spic::internal::systems {
	ScriptSystem::ScriptSystem() 
	{}

	void ScriptSystem::Start(std::vector<std::shared_ptr<spic::GameObject>>& entities, Scene& currentScene)
	{
		for (const auto& script : currentScene.Camera().GetComponents<spic::BehaviourScript>()) {
			script->GameObject(std::make_shared<GameObject>(currentScene.Camera()));
			script->OnStart();
		}
		for (auto& entity : entities) {
			for(const auto& script : entity->GetComponents<spic::BehaviourScript>()){
				script->GameObject(entity);
				script->OnStart();
			}
		}
	}

	void ScriptSystem::Update(std::vector<std::shared_ptr<spic::GameObject>>& entities, Scene& currentScene)
	{
		for(const auto& script : currentScene.Camera().GetComponents<spic::BehaviourScript>()) {
			script->OnUpdate();
		}
		for (auto& entity : entities) {
			for (const auto& script : entity->GetComponents<spic::BehaviourScript>()) {
				script->OnUpdate();
			}
		}
	}
}