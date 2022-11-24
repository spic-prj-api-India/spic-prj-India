#ifndef HULPERFUNCTIONS_H_
#define HULPERFUNCTIONS_H_

#include "Point.hpp"
#include <algorithm>
#include <cmath>
#include <array>
#include "Sprite.hpp"
#include <memory>


namespace spic::HulperFunctions 
{
	/// @brief 
	/// @param org 
	/// @param angle 
	/// @param p 
	void RotatePoint(const Point& org, float angle, Point& p) noexcept;

	/// @brief 
	/// @param pointX 
	/// @param rotation 
	/// @param angle 
	/// @param height 
	/// @param width 
	/// @param scaling 
	/// @return 
	Point GetsPointY(Point& pointX, const Point& rotation, const float angle, float height, float width, float scaling) noexcept;
	
	/// @brief 
	/// @param a 
	/// @param b 
	/// @return 
	bool SpriteSorting(const std::shared_ptr<Sprite> a, const std::shared_ptr<Sprite> b);

	/// @brief 
	/// @param orgin 
	/// @param angle 
	/// @param aspectWidth 
	/// @param aspectHeight 
	/// @return 
	std::array<Point, 4> GetPoints(const Point& orgin, const float angle, const float aspectWidth, const float aspectHeight);

	/// @brief Calculates if a point is within a square
	/// @details https://math.stackexchange.com/a/190373
	/// @param point 
	/// @param square 
	/// @return 
	bool CalculateWithinSquare(const Point& point, std::array<Point, 4>& square);

	/// @brief 
	/// @param point 
	/// @param aspectWidth 
	/// @param aspectHeight 
	/// @return 
	Point GetCenter(const Point& point, const float aspectWidth, const float aspectHeight);

	/// @brief 
	/// @tparam T 
	/// @param n 
	/// @param increment 
	/// @param min 
	/// @param max 
	template <class T>
	void SpecialWrap(T& n, const T increment, const T min, const T max)
	{
		if (n + increment > max)
			n = min;
		else if (n + increment < min)
			n = max;
		else
			n += increment;
	}

	/// @brief 
	/// @tparam T 
	/// @param t 
	/// @return 
	template <class T>
	int PrecisionRoundingoInt(T t)
	{
		return static_cast<int>(t >= 0 ? t - 0.5 : t + 0.5);
	}
}
#endif