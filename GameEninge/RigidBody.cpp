#include "RigidBody.hpp"
#include "GameEngine.hpp"
#include "Box2DExtension.hpp"

namespace spic {
	RigidBody::RigidBody(float _mass, float _gravityScale, BodyType _bodyType) : 
		mass{ _mass }, gravityScale{ _gravityScale }, bodyType{ _bodyType }
	{}

	float RigidBody::GetMass() const 
	{
		return mass;
	}
	float RigidBody::GetGravityScale() const 
	{
		return gravityScale;
	}
	BodyType RigidBody::GetBodyType() const 
	{
		return bodyType;
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