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
	template <class T>
	double DEG2RAD(T DEG)
	{
		return DEG * M_PI / 180.0;
	}

	/**
	 * @brief Convert radians to a degree
	 * @tparam T A floating type
	 * @param RAD 
	 * @return 
	*/
	template <class T>
	double RAD2DEG(T RAD) 
	{
		return RAD * 180.0 / M_PI;
	}
}
#endif