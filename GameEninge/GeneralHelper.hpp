#ifndef GENERALHELPER_H_
#define GENERALHELPER_H_

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#include "Point.hpp"
#include <algorithm>
#include <cmath>
#include <array>
#include "Sprite.hpp"
#include <memory>


namespace spic::GeneralHelper 
{	
	/**
	 * @brief 
	 * @param org 
	 * @param angle 
	 * @param p 
	*/
	void RotatePoint(const Point& org, float angle, Point& p) noexcept;
	
	/**
	 * @brief 
	 * @param pointX 
	 * @param rotation 
	 * @param angle 
	 * @param height 
	 * @param width 
	 * @param scaling 
	 * @return 
	*/
	Point GetsPointY(Point& pointX, const Point& rotation, const float angle, float height, float width, float scaling) noexcept;
	
	/**
	 * @brief 
	 * @param a 
	 * @param b 
	 * @return 
	*/
	bool SpriteSorting(const std::shared_ptr<Sprite> a, const std::shared_ptr<Sprite> b);
	
	/**
	 * @brief 
	 * @param orgin 
	 * @param angle 
	 * @param aspectWidth 
	 * @param aspectHeight 
	 * @return 
	*/
	std::array<Point, 4> GetPoints(const Point& orgin, const float angle, const float aspectWidth, const float aspectHeight);
	
	/**
	 * @brief Calculates if a point is within a square
	 * @param point https://math.stackexchange.com/a/190373
	 * @param square 
	 * @return 
	*/
	bool CalculateWithinSquare(const Point& point, std::array<Point, 4>& square);

	/**
	 * @brief Calculates if a line intersects with another line.
	 *		Sets intersection point and distance to intersection if intersection exists.
	 * @param sPoint1 Start point of line 1
	 * @param ePoint1 End point of line 1
	 * @param sPoint2 Start point of line 2
	 * @param ePoint2 End point of line 2
	 * @param intersectPoint Intersection point
	 * @param distance Distance to intersection
	 * @return
	*/
	bool LineIntersection(Point sPoint1, Point ePoint1, Point sPoint2, Point ePoint2, Point& intersectPoint, float& distance);
	
	/**
	 * @brief 
	 * @param point 
	 * @param aspectWidth 
	 * @param aspectHeight 
	 * @return 
	*/
	Point GetCenter(const Point& point, const float aspectWidth, const float aspectHeight);
	
	/**
	 * @brief 
	 * @tparam T 
	 * @param n 
	 * @param increment 
	 * @param min 
	 * @param max 
	*/
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
	
	/**
	 * @brief 
	 * @tparam T 
	 * @param t 
	 * @return 
	*/
	template <class T>
	int PrecisionRoundingoInt(T t)
	{
		return static_cast<int>(std::lround(t));
	}

	/**
	 * @brief Convert a degree to radians
	 * @tparam T A floating type
	 * @param DEG 
	 * @return 
	*/
	template <typename T, typename R>
	T DEG2RAD(R DEG)
	{
		return static_cast<T>(DEG * M_PI / 180.0);
	}

	/**
	 * @brief Convert radians to a degree
	 * @tparam T A floating type
	 * @param RAD 
	 * @return 
	*/
	template <typename T, typename R>
	T RAD2DEG(R RAD)
	{
		return static_cast<T>(RAD * 180.0 / M_PI);
	}
}
#endif