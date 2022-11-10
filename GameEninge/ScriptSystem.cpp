#include "ScriptSystem.hpp"
#include "BehaviourScript.hpp"


namespace systems {
	ScriptSystem::ScriptSystem() {

	}
	void ScriptSystem::Start(std::vector<std::shared_ptr<spic::GameObject>> entities) {
		for (auto& entity : entities) {
			for(auto script : entity->GetComponents<spic::BehaviourScript>()){
				script->OnStart();
			}
		}
	}
	void ScriptSystem::Update(std::vector<std::shared_ptr<spic::GameObject>> entities) {
		for (auto& entity : entities) {
			for (auto script : entity->GetComponents<spic::BehaviourScript>()) {
				script->OnUpdate();
			}
		}
	}
}