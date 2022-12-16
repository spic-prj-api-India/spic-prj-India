#include "CircleCollider.hpp"
#include <stdexcept>

namespace spic {
	CircleCollider::CircleCollider() : CircleCollider(0.0f)
	{}

	CircleCollider::CircleCollider(const float radius) : Collider()
	{
		Radius(radius);
	}

	Point CircleCollider::Size() const
	{
		const float diameter = radius * 2.0f;
		return { diameter, diameter };
	}

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