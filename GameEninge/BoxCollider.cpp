#include "BoxCollider.hpp"

namespace spic {
	BoxCollider::BoxCollider() : width{ 0.0f }, height{ 0.0f }
	{}

	float BoxCollider::Width() const
	{
		return width;
	}
	void BoxCollider::Width(float newWidth)
	{
		width = newWidth;
	}
	float BoxCollider::Height() const
	{
		return height;
	}
	void BoxCollider::Height(float newHeight)
	{
		height = newHeight;
	}
}