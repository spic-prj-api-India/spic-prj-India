#include "RigidBody.hpp"
#include "GameEngine.hpp"
#include "Box2DExtension.hpp"

namespace spic {
	RigidBody::RigidBody(float _mass, float _gravityScale, spic::BodyType _bodyType) : bodyType{ _bodyType }
	{
		Mass(_mass);
		GravityScale(_gravityScale);
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

	void RigidBody::Mass(float _mass) {
		if (_mass < 0.0f)
			throw std::range_error("Mass can't be below zero");
		mass = _mass;
	}
	void RigidBody::GravityScale(float _gravityScale) {
		if (_gravityScale < 0.0f)
			throw std::range_error("Gravity scale can't be below zero");
		gravityScale = _gravityScale;
	}
	void RigidBody::BodyType(spic::BodyType _bodyType) {
		bodyType = _bodyType;
	}

	void RigidBody::AddForce(std::shared_ptr<spic::GameObject> entity, const Point& forceDirection)
	{
		GameEngine* engine = GameEngine::GetInstance();
		bool exists = engine->HasExtension<extensions::Box2DExtension>();
		if (!exists)
			return;
		std::weak_ptr<extensions::Box2DExtension> physicsExtension = engine->GetExtension<extensions::Box2DExtension>();
		if (auto box2DExtension = physicsExtension.lock())
			box2DExtension->AddForce(entity, forceDirection);
	}
}