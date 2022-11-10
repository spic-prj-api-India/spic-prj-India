#include "PhysicsSystem.hpp"
#include "Box2DExtension.hpp"
#include "GameEngine.hpp"
#include "Collider.hpp"
#include <functional>
#include "Box2DCollisionListener.hpp"
#include "BehaviourScript.hpp"

namespace systems {
	PhysicsSystem::PhysicsSystem() {
		Reset();
	}

	void PhysicsSystem::Reset() {
		GameEngine* engine = GameEngine::GetInstance();
		const bool exists = engine->HasExtension<extensions::Box2DExtension>();
		if (!exists)
			return;
		std::weak_ptr<extensions::Box2DExtension> extension = engine->GetExtension<extensions::Box2DExtension>();
		if (auto physicsExtension = extension.lock()) {
			std::function<void(const std::shared_ptr<spic::GameObject>&, const std::shared_ptr<spic::Collider>&)> enterCallback = [this](const std::shared_ptr<spic::GameObject>& entity, const std::shared_ptr<spic::Collider>& collider) { OnEnter(entity, collider); };
			std::function<void(const std::shared_ptr<spic::GameObject>&, const std::shared_ptr<spic::Collider>&)> exitCallback = [this](const std::shared_ptr<spic::GameObject>& entity, const std::shared_ptr<spic::Collider>& collider) { OnExit(entity, collider); };
			std::function<void(const std::shared_ptr<spic::GameObject>&, const std::shared_ptr<spic::Collider>&)> stayCallback = [this](const std::shared_ptr<spic::GameObject>& entity, const std::shared_ptr<spic::Collider>& collider) { OnStay(entity, collider); };
			Box2DCollisionListener* listener = new Box2DCollisionListener(enterCallback, exitCallback, stayCallback);
			physicsExtension->Reset();
			physicsExtension->RegisterListener(listener);
		}
	}

	void PhysicsSystem::Update(std::vector<std::shared_ptr<spic::GameObject>> entities) {
		// Check if Box2D extension exists and update entities
		GameEngine* engine = GameEngine::GetInstance();
		const bool exists = engine->HasExtension<extensions::Box2DExtension>();
		if (!exists)
			return;
		std::weak_ptr<extensions::Box2DExtension> physicsExtension = engine->GetExtension<extensions::Box2DExtension>();
		if (auto box2DExtension = physicsExtension.lock()) {
			std::vector<std::shared_ptr<spic::GameObject>> physicsEntities = GetPhysicsEntities(entities);
			box2DExtension->Update(physicsEntities);
		}
	}

	void PhysicsSystem::OnEnter(const std::shared_ptr<spic::GameObject>& entity, const std::shared_ptr<spic::Collider>& collider) {
		for (auto script : entity->GetComponents<spic::BehaviourScript>()) {
			script->OnTriggerEnter2D(*collider);
		}
	}

	void PhysicsSystem::OnStay(const std::shared_ptr<spic::GameObject>& entity, const std::shared_ptr<spic::Collider>& collider) {
		for (auto script : entity->GetComponents<spic::BehaviourScript>()) {
			script->OnTriggerStay2D(*collider);
		}
	}

	void PhysicsSystem::OnExit(const std::shared_ptr<spic::GameObject>& entity, const std::shared_ptr<spic::Collider>& collider) {
		for (auto script : entity->GetComponents<spic::BehaviourScript>()) {
			script->OnTriggerExit2D(*collider);
		}
	}

	std::vector<std::shared_ptr<spic::GameObject>> PhysicsSystem::GetPhysicsEntities(std::vector<std::shared_ptr<spic::GameObject>> entities) {
		std::vector<std::shared_ptr<spic::GameObject>> physicsEntities;
		for (auto& entity : entities) {
			const bool isPhysicsEntity = entity->HasComponent<spic::RigidBody>() || entity->HasComponent<spic::Collider>();
			if (isPhysicsEntity)
				physicsEntities.emplace_back(entity);
		}
		return physicsEntities;
	}
}