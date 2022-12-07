#include "RigidBody.hpp"
#include "GameEngine.hpp"
#include "PhysicsExtension1.hpp"

namespace spic {
	RigidBody::RigidBody(float mass, float gravityScale, spic::BodyType _bodyType) : bodyType{_bodyType}
	{
		Mass(mass);
		GravityScale(gravityScale);
	}

	float RigidBody::Mass() const
	{
		return mass;
	}

	float RigidBody::GravityScale() const
	{
		return gravityScale;
	}

	Point RigidBody::Velocity() const
	{
		GameEngine* engine = GameEngine::GetInstance();
		const bool exists = engine->HasExtension<extensions::PhysicsExtension1>();
		if (!exists)
			return { 0.0f, 0.0f };
		std::weak_ptr<extensions::PhysicsExtension1> physicsExtension = engine->GetExtension<extensions::PhysicsExtension1>();
		if (const auto& box2DExtension = physicsExtension.lock())
			return box2DExtension->GetLinearVelocity(this->gameObject->Name());
		return { 0.0f, 0.0f };
	}

	BodyType RigidBody::BodyType() const
	{
		return bodyType;
	}

	void RigidBody::Mass(float newMass) {
		if (newMass < 0.0f)
			throw std::range_error("Mass can't be below zero");
		mass = newMass;
	}

	void RigidBody::GravityScale(float newGravityScale) {
		if (newGravityScale < 0.0f)
			throw std::range_error("Gravity scale can't be below zero");
		gravityScale = newGravityScale;
	}

	void RigidBody::BodyType(spic::BodyType newBodyType) {
		bodyType = newBodyType;
	}

	void RigidBody::AddForce(const Point& forceDirection)
	{
		GameEngine* engine = GameEngine::GetInstance();
		const bool exists = engine->HasExtension<extensions::PhysicsExtension1>();
		if (!exists)
			return;
		std::weak_ptr<extensions::PhysicsExtension1> physicsExtension = engine->GetExtension<extensions::PhysicsExtension1>();
		if (const auto& box2DExtension = physicsExtension.lock())
			box2DExtension->AddForce(GameObject::GetByName(this->gameObject->Name()), forceDirection);
	}
}