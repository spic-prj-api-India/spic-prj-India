#include "CircleCollider.hpp"

namespace spic {
	CircleCollider::CircleCollider() : radius{ 0.0f }
	{}

	float CircleCollider::Radius() const
	{
		return radius;
	}
	void CircleCollider::Radius(float newRadius)
	{
		radius = newRadius;
	}
}