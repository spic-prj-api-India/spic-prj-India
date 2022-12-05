#include "Point.hpp"
#include <cfloat>
#include <corecrt_math.h>

namespace spic {
	Point::Point() : x { 0.0f }, y { 0.0f } 
	{
	}
	
	float Point::Normalize()
	{
		float length = sqrtf(x * x + y * y);
		if (length < FLT_EPSILON)
		{
			return 0.0f;
		}
		float invLength = 1.0f / length;
		x *= invLength;
		y *= invLength;

		return length;
	}

	Point Point::operator +(const Point& point)
	{
		return Point(this->x + point.x, this->y + point.y);
	}

	void Point::operator +=(const Point& point)
	{
		this->x += point.x;
		this->y += point.y;
	}

	Point Point::operator -(const Point& point)
	{
		return Point(this->x - point.x, this->y - point.y);
	}

	void Point::operator -=(const Point& point)
	{
		this->x -= point.x;
		this->y -= point.y;
	}

	Point Point::operator*(const Point& point)
	{
		return Point(this->x * point.x, this->y * point.y);
	}

	Point Point::operator /(const Point& point)
	{
		return Point(this->x / point.x, this->y / point.y);
	}

	Point Point::operator +(const float value)
	{
		return Point(this->x + value, this->y + value);
	}

	void Point::operator +=(const float value)
	{
		this->x += value;
		this->y += value;
	}

	Point Point::operator -(const float value)
	{
		return Point(this->x - value, this->y - value);
	}

	void Point::operator -=(const float value)
	{
		this->x -= value;
		this->y -= value;
	}

	Point Point::operator*(const float value)
	{
		return Point(this->x * value, this->y * value);
	}

	Point Point::operator /(const float value)
	{
		return Point(this->x / value, this->y / value);
	}

	float Point::DotProduct(const Point& point)
	{
		return this->x * point.x + this->y * point.y;
	}
}
