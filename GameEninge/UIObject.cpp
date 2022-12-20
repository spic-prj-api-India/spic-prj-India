#include "UIObject.hpp"

namespace spic {
	UIObject::UIObject() : GameObject(), width{ 0.0f }, height{ 0.0f }
	{
	}

	UIObject::UIObject(const float width, const float height)
	{
		this->width = width;
		this->height = height;
	}

	float UIObject::Width() const
	{
		return this->width;
	}

	float UIObject::Height() const
	{
		return this->height;
	}

	void UIObject::Width(const float newWidth)
	{
		this->width = newWidth;
	}

	void UIObject::Height(const float newHeight)
	{
		this->height = newHeight;
	}
}