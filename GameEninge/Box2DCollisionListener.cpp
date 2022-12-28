#include "Box2DCollisionListener.hpp"

namespace spic::internal::extensions
{
	Box2DCollisionListener::Box2DCollisionListener() : Box2DCollisionListener(nullptr, nullptr, nullptr)
	{
	}

	Box2DCollisionListener::Box2DCollisionListener(CollisionCallback enterCallback, CollisionCallback exitCallback, CollisionCallback stayCallback)
		: onEnterCallback{ enterCallback }, onExitCallback{ exitCallback }, onStayCallback{ stayCallback }
	{
	}

	void Box2DCollisionListener::BeginContact(b2Contact* contact)
	{
		// Get contact bodies
		b2Body* bodyA = contact->GetFixtureA()->GetBody();
		b2Body* bodyB = contact->GetFixtureB()->GetBody();

		// Check if fixture A and B are an entity
		uintptr_t bodyDataA = bodyA->GetUserData().pointer;
		uintptr_t bodyDataB = bodyB->GetUserData().pointer;
		if (!bodyDataA || !bodyDataB)
			return;

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

	void Box2DCollisionListener::EndContact(b2Contact* contact)
	{
		// Get contact bodies
		b2Body* bodyA = contact->GetFixtureA()->GetBody();
		b2Body* bodyB = contact->GetFixtureB()->GetBody();

		// Check if fixture A and B are an entity
		uintptr_t bodyDataA = bodyA->GetUserData().pointer;
		uintptr_t bodyDataB = bodyB->GetUserData().pointer;
		if (!bodyDataA || !bodyDataB)
			return;

		// Convert to game object
		spic::GameObject* entityA = reinterpret_cast<spic::GameObject*>(bodyDataA);
		spic::GameObject* entityB = reinterpret_cast<spic::GameObject*>(bodyDataB);
		std::shared_ptr<spic::GameObject> sharedPtrA = std::make_shared<spic::GameObject>(*entityA);
		std::shared_ptr<spic::GameObject> sharedPtrB = std::make_shared<spic::GameObject>(*entityB);

		// Get colliders
		std::shared_ptr<spic::Collider> colliderA = std::move(entityA->GetComponent<spic::Collider>());
		std::shared_ptr<spic::Collider> colliderB = std::move(entityB->GetComponent<spic::Collider>());

		// Call callbacks
		onExitCallback(std::move(sharedPtrA), std::move(colliderB));
		onExitCallback(std::move(sharedPtrB), std::move(colliderA));
	}

	void Box2DCollisionListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
	{
		// Get contact bodies
		b2Body* bodyA = contact->GetFixtureA()->GetBody();
		b2Body* bodyB = contact->GetFixtureB()->GetBody();

		// Check if fixture A and B are an entity
		uintptr_t bodyDataA = bodyA->GetUserData().pointer;
		uintptr_t bodyDataB = bodyB->GetUserData().pointer;
		if (!bodyDataA || !bodyDataB)
			return;

		// Convert to game object
		spic::GameObject* entityA = reinterpret_cast<spic::GameObject*>(bodyDataA);
		spic::GameObject* entityB = reinterpret_cast<spic::GameObject*>(bodyDataB);
		std::shared_ptr<spic::GameObject> sharedPtrA = std::make_shared<spic::GameObject>(*entityA);
		std::shared_ptr<spic::GameObject> sharedPtrB = std::make_shared<spic::GameObject>(*entityB);

		// Get colliders
		std::shared_ptr<spic::Collider> colliderA = std::move(entityA->GetComponent<spic::Collider>());
		std::shared_ptr<spic::Collider> colliderB = std::move(entityB->GetComponent<spic::Collider>());

		// Call callbacks
		onStayCallback(std::move(sharedPtrA), std::move(colliderB));
		onStayCallback(std::move(sharedPtrB), std::move(colliderA));
	}

	void Box2DCollisionListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
	{
	}
}