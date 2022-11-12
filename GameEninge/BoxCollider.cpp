#include "BoxCollider.hpp"
#include <stdexcept>

namespace spic {
	BoxCollider::BoxCollider() : width{ 0.0f }, height{ 0.0f }
	{}

	float BoxCollider::Width() const
	{
		return width;
	}
	void BoxCollider::Width(float newWidth)
	{
		if (newWidth < 0.0f)
			throw std::range_error("Width can't be below zero");
		width = newWidth;
	}
	float BoxCollider::Height() const
	{
		return height;
	}
	void BoxCollider::Height(float newHeight)
	{
		if (newHeight < 0.0f)
			throw std::range_error("Height can't be below zero");
		height = newHeight;
	}
}