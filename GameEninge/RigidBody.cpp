#include "RigidBody.hpp"

namespace spic {
	RigidBody::RigidBody(float _mass, float _gravityScale, BodyType _bodyType) {
		mass = _mass;
		gravityScale = _gravityScale;
		bodyType = _bodyType;
	}
	float RigidBody::GetMass() const {
		return mass;
	}
	float RigidBody::GetGravityScale() const {
		return gravityScale;
	}
	BodyType RigidBody::GetBodyType() const {
		return bodyType;
	}
}