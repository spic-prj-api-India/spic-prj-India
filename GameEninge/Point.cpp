#include "Point.hpp"
#include <cfloat>
#include <corecrt_math.h>
#include "Defaults.hpp"

namespace spic {
	float Point::Length() const
	{
		return sqrtf(x * x + y * y);
	}

	float Point::LengthSq() const
	{
		return (x * x + y * y);
	}

	float Point::Normalize()
	{
		const float length = Length();

		if (length < FLT_EPSILON)
		{
			return 0.0f;
		}

		const float invLength = 1.0f / length;
		x *= invLength;
		y *= invLength;

		return length;
	}

	float Point::Distance(const Point& point) const
	{
		return sqrtf(powf(this->x - point.x, 2) + powf(this->y - point.y, 2));
	}

	Point Point::Perp() const
	{
		return { -y, x };
	}

	float Point::Rotation() const
	{
		if (y <= 0) 
			return asinf(x / sqrtf(x * x + y * y)) * 180.f / spic::internal::defaults::PI;
		
		if (x == 0) 
			return 180.f;
		
		if (x > 0) 
			return atanf(y / x) * 180.f / spic::internal::defaults::PI + 90.f;
		
		return atanf(y / x) * 180.f / spic::internal::defaults::PI - 90.f;
	}

	bool Point::Accumulate(Point& force, const float maxForce)
	{
		const float magnitudeSoFar = Length();
		//calculate how much steering force remains to be used by this vehicle
		float magnitudeRemaining = maxForce - magnitudeSoFar;
		//return false if there is no more force left to use
		if (magnitudeRemaining <= 0.0) return false;
		//calculate the magnitude of the force we want to add
		const float magnitudeToAdd = force.Length();
		//if the magnitude of the sum of ForceToAdd and the running total
		//does not exceed the maximum force available to this vehicle, just
		//add together. Otherwise add as much of the ForceToAdd vector as
		//possible without going over the max.
		if (magnitudeToAdd >= magnitudeRemaining)
		{
			force.Normalize();
			force *= magnitudeRemaining;
			this->x += force.x;
			this->y += force.y;
			return false;
		}
		//add the remaining magnitude
		this->x += force.x;
		this->y += force.y;
		return true;
	}

	Point Point::operator +(const Point& point) const
	{
		return Point(this->x + point.x, this->y + point.y);
	}

	void Point::operator +=(const Point& point)
	{
		this->x += point.x;
		this->y += point.y;
	}

	Point Point::operator -(const Point& point) const
	{
		return Point(this->x - point.x, this->y - point.y);
	}

	void Point::operator -=(const Point& point)
	{
		this->x -= point.x;
		this->y -= point.y;
	}

	Point Point::operator*(const Point& point) const
	{
		return Point(this->x * point.x, this->y * point.y);
	}

	void Point::operator *=(const Point& point)
	{
		this->x *= point.x;
		this->y *= point.y;
	}

	Point Point::operator /(const Point& point) const
	{
		return Point(this->x / point.x, this->y / point.y);
	}

	void Point::operator /=(const Point& point)
	{
		this->x /= point.x;
		this->y /= point.y;
	}

	Point Point::operator +(const float value) const
	{
		return Point(this->x + value, this->y + value);
	}

	void Point::operator +=(const float value)
	{
		this->x += value;
		this->y += value;
	}

	Point Point::operator -(const float value) const
	{
		return Point(this->x - value, this->y - value);
	}

	void Point::operator -=(const float value)
	{
		this->x -= value;
		this->y -= value;
	}

	Point Point::operator*(const float value) const
	{
		return Point(this->x * value, this->y * value);
	}

	void Point::operator *=(const float value)
	{
		this->x *= value;
		this->y *= value;
	}

	Point Point::operator /(const float value) const
	{
		return Point(this->x / value, this->y / value);
	}

	void Point::operator /=(const float value)
	{
		this->x /= value;
		this->y /= value;
	}

	bool Point::operator==(const Point value) const
	{
		return this->x == value.x && this->y == value.y;
	}

	bool Point::operator<(const Point& cp) const noexcept
	{
		return Length() < cp.Length();
	}

	float Point::Dot(const Point& point) const
	{
		return this->x * point.x + this->y * point.y;
	}
}
