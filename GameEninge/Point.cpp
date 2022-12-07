#include "Point.hpp"
#include <cfloat>
#include <corecrt_math.h>

namespace spic {
	float Point::Length() const
	{
		return sqrtf(x * x + y * y);
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

	float Point::Distance(const Point& point) const
	{
		return sqrtf(powf(this->x - point.x, 2) + powf(this->y - point.y, 2));
	}

	bool Point::Accumulate(Point& point, const float maxForce)
	{
		const float MagnitudeSoFar = Length();
		//calculate how much steering force remains to be used by this vehicle
		const float MagnitudeRemaining = maxForce - MagnitudeSoFar;
		//return false if there is no more force left to use
		if (MagnitudeRemaining <= 0.0) return false;
		//calculate the magnitude of the force we want to add
		const float MagnitudeToAdd = point.Length();
		//if the magnitude of the sum of ForceToAdd and the running total
		//does not exceed the maximum force available to this vehicle, just
		//add together. Otherwise add as much of the ForceToAdd vector as
		//possible without going over the max.
		if (MagnitudeToAdd < MagnitudeRemaining)
		{
			this->x += point.x;
			this->y += point.y;
		}
		else
		{
			//add it to the steering force
			point.Normalize();
			const Point force = point * MagnitudeRemaining;
			this->x += force.x;
			this->y += force.y;
		}
		return true;
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

	void Point::operator *=(const Point& point)
	{
		this->x *= point.x;
		this->y *= point.y;
	}

	Point Point::operator /(const Point& point)
	{
		return Point(this->x / point.x, this->y / point.y);
	}

	void Point::operator /=(const Point& point)
	{
		this->x /= point.x;
		this->y /= point.y;
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

	void Point::operator *=(const float value)
	{
		this->x *= value;
		this->y *= value;
	}

	Point Point::operator /(const float value)
	{
		return Point(this->x / value, this->y / value);
	}

	void Point::operator /=(const float value)
	{
		this->x /= value;
		this->y /= value;
	}

	float Point::DotProduct(const Point& point)
	{
		return this->x * point.x + this->y * point.y;
	}
}
