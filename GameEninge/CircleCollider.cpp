#include "CircleCollider.hpp"
#include <stdexcept>

namespace spic {
	CircleCollider::CircleCollider() : radius{ 0.0f }
	{}

	float CircleCollider::Radius() const
	{
		return radius;
	}
	void CircleCollider::Radius(const float newRadius)
	{
		if (newRadius < 0.0f)
			throw std::range_error("Radius can't be below zero");
		radius = newRadius;
	}
}