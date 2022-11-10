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
		onStays;
		GameEngine* engine = GameEngine::GetInstance();
		const bool exists = engine->HasExtension<extensions::Box2DExtension>();
		if (!exists)
			return;
		std::weak_ptr<extensions::Box2DExtension> extension = engine->GetExtension<extensions::Box2DExtension>();
		if (auto physicsExtension = extension.lock()) {
			std::function<void(const std::shared_ptr<spic::GameObject>&, const std::shared_ptr<spic::Collider>&)> enterCallback = [this](const std::shared_ptr<spic::GameObject>& entity, const std::shared_ptr<spic::Collider>& collider) { OnEnter(entity, collider); };
			std::function<void(const std::shared_ptr<spic::GameObject>&, const std::shared_ptr<spic::Collider>&)> exitCallback = [this](const std::shared_ptr<spic::GameObject>& entity, const std::shared_ptr<spic::Collider>& collider) { OnExit(entity, collider); };
			std::unique_ptr<Box2DCollisionListener> listener = std::make_unique<Box2DCollisionListener>(enterCallback, exitCallback);
			physicsExtension->Reset();
			physicsExtension->RegisterListener(std::move(listener));
		}
	}

	void PhysicsSystem::Update(std::vector<std::shared_ptr<spic::GameObject>> entities) {
		std::vector<std::shared_ptr<spic::GameObject>> physicsEntities = GetPhysicsEntities(entities);
		// Check for collisions
		OnStay(physicsEntities);
		// Check if Box2D extension exists and update entities
		GameEngine* engine = GameEngine::GetInstance();
		const bool exists = engine->HasExtension<extensions::Box2DExtension>();
		if (!exists)
			return;
		std::weak_ptr<extensions::Box2DExtension> physicsExtension = engine->GetExtension<extensions::Box2DExtension>();
		if (auto box2DExtension = physicsExtension.lock()) {
			box2DExtension->Update(physicsEntities);
		}
	}

	void PhysicsSystem::OnEnter(const std::shared_ptr<spic::GameObject>& entity, const std::shared_ptr<spic::Collider>& collider) {
		const std::string tag = entity->Tag();
		if (onStays.find(tag) == onStays.end()) {
			onStays[tag];
		}
		onStays[tag].emplace_back(collider);
		for (auto script : entity->GetComponents<spic::BehaviourScript>()) {
			script->OnTriggerEnter2D(*collider);
		}
	}

	void PhysicsSystem::OnStay(std::vector<std::shared_ptr<spic::GameObject>> entities) {
		for (auto entity : entities) {
			std::string tag = entity->Tag();
			if (onStays.find(tag) == onStays.end())
				continue;
			auto colliders = onStays[tag];
			for (auto script : entity->GetComponents<spic::BehaviourScript>()) {
				for (const auto collider : colliders) {
					script->OnTriggerStay2D((*collider));
				}
			}
		}
	}

	void PhysicsSystem::OnExit(const std::shared_ptr<spic::GameObject>& entity, const std::shared_ptr<spic::Collider>& collider) {
		const std::string tag = entity->Tag();
		//onStays[tag].erase(std::remove(onStays[tag].begin(), onStays[tag].end(), collider), onStays[tag].end());
		if (onStays[tag].size() == 0)
			onStays.erase(tag);
		for (auto script : entity->GetComponents<spic::BehaviourScript>()) {
			script->OnTriggerEnter2D(*collider);
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