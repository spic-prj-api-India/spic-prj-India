#include "RigidBody.hpp"
#include "GameEngine.hpp"
#include "PhysicsExtension1.hpp"

namespace spic {
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

	void RigidBody::AddForce(std::shared_ptr<spic::GameObject> entity, const Point& forceDirection)
	{
		GameEngine* engine = GameEngine::GetInstance();
		bool exists = engine->HasExtension<extensions::PhysicsExtension1>();
		if (!exists)
			return;
		std::weak_ptr<extensions::PhysicsExtension1> physicsExtension = engine->GetExtension<extensions::PhysicsExtension1>();
		if (auto box2DExtension = physicsExtension.lock())
			box2DExtension->AddForce(entity, forceDirection);
	}
}