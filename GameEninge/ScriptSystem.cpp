#include "ScriptSystem.hpp"
#include "BehaviourScript.hpp"


namespace spic::internal::systems {
	ScriptSystem::ScriptSystem() 
	{}

	void ScriptSystem::Start(std::vector<std::shared_ptr<spic::GameObject>>& entities) const
	{
		for (auto& entity : entities) {
			for(const auto& script : entity->GetComponents<spic::BehaviourScript>()){
				script->GameObject(entity);
				script->OnStart();
			}
		}
	}

	void ScriptSystem::Update(std::vector<std::shared_ptr<spic::GameObject>>& entities, Scene& currentScene)
	{
		for (auto& entity : entities) {
			for (const auto& script : entity->GetComponents<spic::BehaviourScript>()) {
				script->OnUpdate();
			}
		}
	}
}