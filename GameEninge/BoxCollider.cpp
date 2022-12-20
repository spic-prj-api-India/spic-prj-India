#include "BoxCollider.hpp"
#include <stdexcept>

namespace spic {
	BoxCollider::BoxCollider() : BoxCollider(0.0f, 0.0f)
	{}

	BoxCollider::BoxCollider(const float width, const float height) : Collider()
	{
		Width(width);
		Height(height);
	}

	Point BoxCollider::Size() const
	{
		return { width, height };
	}

	float BoxCollider::Width() const
	{
		return width;
	}

	void BoxCollider::Width(const float newWidth)
	{
		if (newWidth < 0.0f)
			throw std::range_error("Width can't be below zero");

		width = newWidth;
	}

	float BoxCollider::Height() const
	{
		return height;
	}

	void BoxCollider::Height(const float newHeight)
	{
		if (newHeight < 0.0f)
			throw std::range_error("Height can't be below zero");

		height = newHeight;
	}
}