#include "PhysicsSystem.hpp"
#include "IPhysicsExtension.hpp"
#include "GameEngine.hpp"
#include "Collider.hpp"
#include <functional>
#include "Box2DCollisionListener.hpp"
#include "BehaviourScript.hpp"

namespace spic::internal::systems {
	PhysicsSystem::PhysicsSystem() 
	{
		Reset();
	}

	void PhysicsSystem::Reset() const
	{
		spic::GameEngine* engine = spic::GameEngine::GetInstance();
		std::vector<std::weak_ptr<spic::extensions::IPhysicsExtension>> physicsExtensions = engine->GetExtensions<spic::extensions::IPhysicsExtension>();
		for (const auto& extension : physicsExtensions) {
			if (const auto& physicsExtension = extension.lock()) {
				std::function<void(const std::shared_ptr<spic::GameObject>&, const std::shared_ptr<spic::Collider>&)> enterCallback = [this](const std::shared_ptr<spic::GameObject>& entity, const std::shared_ptr<spic::Collider>& collider) { OnEnter(entity, collider); };
				std::function<void(const std::shared_ptr<spic::GameObject>&, const std::shared_ptr<spic::Collider>&)> exitCallback = [this](const std::shared_ptr<spic::GameObject>& entity, const std::shared_ptr<spic::Collider>& collider) { OnExit(entity, collider); };
				std::function<void(const std::shared_ptr<spic::GameObject>&, const std::shared_ptr<spic::Collider>&)> stayCallback = [this](const std::shared_ptr<spic::GameObject>& entity, const std::shared_ptr<spic::Collider>& collider) { OnStay(entity, collider); };
				spic::extensions::ICollisionListener* listener = new extensions::Box2DCollisionListener(enterCallback, exitCallback, stayCallback);
				physicsExtension->Reset();
				physicsExtension->RegisterListener(listener);
			}
		}
	}

	void PhysicsSystem::Update(std::vector<std::shared_ptr<spic::GameObject>>& entities, Scene& currentScene)
	{
		// Check if Box2D extension exists and update entities
		spic::GameEngine* engine = spic::GameEngine::GetInstance();
		std::vector<std::weak_ptr<spic::extensions::IPhysicsExtension>> physicsExtensions = engine->GetExtensions<spic::extensions::IPhysicsExtension>();
		for (const auto& extension : physicsExtensions) {
			if (const auto& physicsExtension = extension.lock()) {
				std::vector<std::shared_ptr<spic::GameObject>> physicsEntities = GetPhysicsEntities(entities);
				physicsExtension->Update(physicsEntities);
			}
		}
	}

	void PhysicsSystem::OnEnter(const std::shared_ptr<spic::GameObject>& entity, const std::shared_ptr<spic::Collider>& collider) const
	{
		for (const auto& script : entity->GetComponents<spic::BehaviourScript>()) {
			script->OnTriggerEnter2D(*collider);
		}
	}

	void PhysicsSystem::OnStay(const std::shared_ptr<spic::GameObject>& entity, const std::shared_ptr<spic::Collider>& collider) const
	{
		for (const auto& script : entity->GetComponents<spic::BehaviourScript>()) {
			script->OnTriggerStay2D(*collider);
		}
	}

	void PhysicsSystem::OnExit(const std::shared_ptr<spic::GameObject>& entity, const std::shared_ptr<spic::Collider>& collider) const
	{
		for (const auto& script : entity->GetComponents<spic::BehaviourScript>()) {
			script->OnTriggerExit2D(*collider);
		}
	}

	std::vector<std::shared_ptr<spic::GameObject>> PhysicsSystem::GetPhysicsEntities(std::vector<std::shared_ptr<spic::GameObject>> entities) const
	{
		std::vector<std::shared_ptr<spic::GameObject>> physicsEntities;
		for (const auto& entity : entities) {
			if (IsPhysicsEntity(entity))
				physicsEntities.emplace_back(entity);
			for (const auto& child : entity->GetChildren()){
				if (IsPhysicsEntity(child))
					physicsEntities.emplace_back(child);
			}
		}
		return physicsEntities;
	}

	bool PhysicsSystem::IsPhysicsEntity(const std::shared_ptr<spic::GameObject>& entity) const
	{
		return entity->HasComponent<spic::RigidBody>() || entity->HasComponent<spic::Collider>();
	}
}