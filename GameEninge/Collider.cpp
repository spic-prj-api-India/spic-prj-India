#include "Collider.hpp"

using namespace spic;

Collider::Collider() : Collider(0.3f, 0.5f)
{}

Collider::Collider(const float friction, const float bounciness) : friction{ friction }, bounciness{ bounciness }, enabled{ true }
{}

float Collider::Friction() const
{
	return this->friction;
}

void Collider::Friction(const float newFriction)
{
	this->friction = newFriction;
}

float Collider::Bounciness() const
{
	return this->bounciness;
}

void Collider::Bounciness(const float newBounciness)
{
	this->bounciness = newBounciness;
}

bool Collider::Enabled() const
{
	return this->enabled;
}

void Collider::Disable()
{
	this->enabled = false;
}

void Collider::Enable() {
	this->enabled = true;
}