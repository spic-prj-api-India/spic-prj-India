#include "Box2DCollisionListener.hpp"

namespace spic::internal::extensions {
	Box2DCollisionListener::Box2DCollisionListener() : Box2DCollisionListener(nullptr, nullptr, nullptr)
	{
	}

	Box2DCollisionListener::Box2DCollisionListener(
		std::function<void(const std::shared_ptr<spic::GameObject>, const std::shared_ptr<spic::Collider>)> enterCallback,
		std::function<void(const std::shared_ptr<spic::GameObject>, const std::shared_ptr<spic::Collider>)> exitCallback,
		std::function<void(const std::shared_ptr<spic::GameObject>, const std::shared_ptr<spic::Collider>)> stayCallback) 
		: onEnterCallback{ enterCallback }, onExitCallback{ exitCallback }, onStayCallback{ stayCallback }
	{
	}

	void Box2DCollisionListener::BeginContact(b2Contact* contact)
	{
		// Check if fixture A and B are an entity
		uintptr_t bodyDataA = contact->GetFixtureA()->GetBody()->GetUserData().pointer;
		uintptr_t bodyDataB = contact->GetFixtureB()->GetBody()->GetUserData().pointer;
		if (bodyDataA && bodyDataB)
		{
			// Convert to game object
			spic::GameObject* entityA = reinterpret_cast<spic::GameObject*>(bodyDataA);
			spic::GameObject* entityB = reinterpret_cast<spic::GameObject*>(bodyDataB);
			std::shared_ptr<spic::GameObject> sharedPtrA = std::make_shared<spic::GameObject>(*entityA);
			std::shared_ptr<spic::GameObject> sharedPtrB = std::make_shared<spic::GameObject>(*entityB);

			// Get colliders
			std::shared_ptr<spic::Collider> colliderA = entityA->GetComponent<spic::Collider>();
			std::shared_ptr<spic::Collider> colliderB = entityB->GetComponent<spic::Collider>();

			// Call callbacks
			onEnterCallback(sharedPtrA, colliderB);
			onEnterCallback(sharedPtrB, colliderA);
		}
	}

	void Box2DCollisionListener::EndContact(b2Contact* contact)
	{
		// Check if fixture A and B are an entity
		uintptr_t bodyDataA = contact->GetFixtureA()->GetBody()->GetUserData().pointer;
		uintptr_t bodyDataB = contact->GetFixtureB()->GetBody()->GetUserData().pointer;
		if (bodyDataA && bodyDataB)
		{
			// Convert to game object
			spic::GameObject* entityA = reinterpret_cast<spic::GameObject*>(bodyDataA);
			spic::GameObject* entityB = reinterpret_cast<spic::GameObject*>(bodyDataB);
			std::shared_ptr<spic::GameObject> sharedPtrA = std::make_shared<spic::GameObject>(*entityA);
			std::shared_ptr<spic::GameObject> sharedPtrB = std::make_shared<spic::GameObject>(*entityB);

			// Get colliders
			std::shared_ptr<spic::Collider> colliderA = entityA->GetComponent<spic::Collider>();
			std::shared_ptr<spic::Collider> colliderB = entityB->GetComponent<spic::Collider>();

			// Call callbacks
			onExitCallback(sharedPtrA, colliderB);
			onExitCallback(sharedPtrB, colliderA);
		}
	}

	void Box2DCollisionListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
	{
		// Check if fixture A and B are an entity
		uintptr_t bodyDataA = contact->GetFixtureA()->GetBody()->GetUserData().pointer;
		uintptr_t bodyDataB = contact->GetFixtureB()->GetBody()->GetUserData().pointer;
		if (bodyDataA && bodyDataB)
		{
			// Convert to game object
			spic::GameObject* entityA = reinterpret_cast<spic::GameObject*>(bodyDataA);
			spic::GameObject* entityB = reinterpret_cast<spic::GameObject*>(bodyDataB);
			std::shared_ptr<spic::GameObject> sharedPtrA = std::make_shared<spic::GameObject>(*entityA);
			std::shared_ptr<spic::GameObject> sharedPtrB = std::make_shared<spic::GameObject>(*entityB);

			// Get colliders
			std::shared_ptr<spic::Collider> colliderA = entityA->GetComponent<spic::Collider>();
			std::shared_ptr<spic::Collider> colliderB = entityB->GetComponent<spic::Collider>();

			// Call callbacks
			onStayCallback(sharedPtrA, colliderB);
			onStayCallback(sharedPtrB, colliderA);
		}
	}

	void Box2DCollisionListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
	{
	}
}