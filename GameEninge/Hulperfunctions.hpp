#pragma once
#include "Point.hpp"
#include <algorithm>
#include <cmath>

namespace spic::HulperFunctions 
{
	template <class T>
	static int PrecisionRoundingoInt(T t)
	{
		return static_cast<int>(t >= 0 ? t - 0.5 : t + 0.5);
	}

	static void RotatePoint(const Point& org, float angle, Point& p) noexcept
	{
		p = Point{ std::cos(angle) * (p.x - org.x) - std::sin(angle) * (p.y - org.y) + org.x,
			std::sin(angle) * (p.x - org.x) + std::cos(angle) * (p.y - org.y) + org.y };
	}

	static Point GetsPointY(Point& pointX, const Point& rotation, const float angle, float height, float width, float scaling) noexcept
	{
		RotatePoint(rotation, angle, pointX);
		return Point{ pointX.x * scaling, pointX.y * height * scaling };
	}
}