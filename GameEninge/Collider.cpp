#include "Collider.hpp"

using namespace spic;

Collider::Collider() : Collider(0.3f, 0.5f)
{}

Collider::Collider(const float friction, const float bounciness) : friction{ friction }, enabled{ true }
{
	Bounciness(bounciness);
}

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
	if (newBounciness < 0 || newBounciness > 1)
		throw std::exception("Bounciness needs to be between 0 and 1");
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