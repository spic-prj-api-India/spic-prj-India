#include "RigidBody.hpp"
#include "GameEngine.hpp"
#include "PhysicsExtension1.hpp"

namespace spic 
{
	RigidBody::RigidBody(const float mass, const float gravityScale, const spic::BodyType _bodyType) : bodyType{ _bodyType }
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
		const bool exists = engine->HasExtension<extensions::IPhysicsExtension>();
		if (!exists)
			return { 0.0f, 0.0f };

		std::weak_ptr<extensions::IPhysicsExtension> extension = engine->GetExtension<extensions::IPhysicsExtension>();
		if (const auto& physicsExtension = extension.lock())
			return physicsExtension->GetLinearVelocity(this->gameObject->Name());

		return { 0.0f, 0.0f };
	}

	BodyType RigidBody::BodyType() const
	{
		return bodyType;
	}

	void RigidBody::Mass(const float newMass) {
		if (newMass < 0.0f)
			throw std::range_error("Mass can't be below zero");

		mass = newMass;
	}

	void RigidBody::GravityScale(const float newGravityScale) {
		if (newGravityScale < 0.0f)
			throw std::range_error("Gravity scale can't be below zero");

		gravityScale = newGravityScale;
	}

	void RigidBody::BodyType(const spic::BodyType newBodyType) {
		bodyType = newBodyType;
	}

	void RigidBody::AddForce(const Point& forceDirection)
	{
		GameEngine* engine = GameEngine::GetInstance();
		const bool exists = engine->HasExtension<extensions::IPhysicsExtension>();
		if (!exists)
			return;

		std::weak_ptr<extensions::IPhysicsExtension> extension = engine->GetExtension<extensions::IPhysicsExtension>();
		if (const auto& physicsExtension = extension.lock()) {
			const auto& existingGameObject = GameObject::Find(this->gameObject->Name());
			if (existingGameObject == nullptr)
				return;
			physicsExtension->AddForce(existingGameObject, forceDirection);
		}
	}
}