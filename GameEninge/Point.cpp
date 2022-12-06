#include "Point.hpp"
#include <cfloat>
#include <corecrt_math.h>

namespace spic {
	#define self (*this)

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

	float Point::Length() const
	{
		return sqrtf(x * x + y * y);
	}

	bool Point::Accumulate(Point& point, const float maxForce)
	{
		float MagnitudeSoFar = self.Length();
		//calculate how much steering force remains to be used by this vehicle
		float MagnitudeRemaining = maxForce - MagnitudeSoFar;
		//return false if there is no more force left to use
		if (MagnitudeRemaining <= 0.0) return false;
		//calculate the magnitude of the force we want to add
		float MagnitudeToAdd = point.Length();
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
			const float force = MagnitudeRemaining * point.Normalize();
			this->x += force;
			this->y += force;
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