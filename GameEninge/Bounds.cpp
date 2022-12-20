#include "Bounds.hpp"

namespace spic {
	Bounds::Bounds() 
		: width{ 0.0f }
		, height{ 0.0f }
		, top{ 0.0f }
		, right{ 0.0f }
		, bottom{ 0.0f }
		, left{0.0f}
	{}

	Bounds::Bounds(const Point& v) 
		: width{ v.x }
		, height{ v.y }
		, top{ 0.0f }
		, right{ v.x }
		, bottom{ v.y }
		, left{ 0.0f }
	{}

	Bounds::Bounds(const float x, const float y, const float w, const float h) 
		: width{ w }
		, height{ h }
		, top{ y }
		, right{ x + w }
		, bottom{ y + height }
		, left{ x }
	{}

	float Bounds::Width() const
	{
		return width;
	}

	float Bounds::Height() const
	{
		return height;
	}

	float Bounds::Top() const
	{
		return top;
	}

	float Bounds::Bottom() const
	{
		return bottom;
	}

	float Bounds::Left() const
	{
		return left;
	}

	float Bounds::Right() const
	{
		return right;
	}

	bool Bounds::InBounds(Point point) const
	{
		if (point.x < left) 
			return false;

		if (point.x >= left + width) 
			return false;

		if (point.y < top) 
			return false;

		if (point.y >= top + height) 
			return false;

		return true;
	}
}