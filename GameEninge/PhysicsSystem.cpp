#include "PhysicsSystem.hpp"
#include "Box2DExtension.hpp"
#include "GameEngine.hpp"
#include "Collider.hpp"

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
		if (auto physicsExtension = extension.lock())
			physicsExtension->Reset();
	}

	void PhysicsSystem::Update(std::vector<std::shared_ptr<spic::GameObject>> entities) {
		// Filter entities
		std::vector<std::shared_ptr<spic::GameObject>> physicsEntities = std::vector<std::shared_ptr<spic::GameObject>>();
		for (auto& entity : entities) {
			const bool isPhysicsEntity = entity->HasComponent<spic::RigidBody>() || entity->HasComponent<spic::Collider>();
			if (isPhysicsEntity)
				physicsEntities.emplace_back(entity);
		}

		// Check if Box2D extension exists
		GameEngine* engine = GameEngine::GetInstance();
		const bool exists = engine->HasExtension<extensions::Box2DExtension>();
		if (!exists)
			return;
		std::weak_ptr<extensions::Box2DExtension> physicsExtension = engine->GetExtension<extensions::Box2DExtension>();
		if (auto box2DExtension = physicsExtension.lock())
			box2DExtension->Update(physicsEntities);
	}
}