#include "Point.hpp"
#include <cfloat>
#include <corecrt_math.h>
#include "Defaults.hpp"

namespace spic 
{
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
		if (y == 0 && x == 0)
			return 0.0f;
		if (y <= 0) 
			return asinf(x / sqrtf(x * x + y * y)) * 180.f / spic::internal::defaults::PI;
		
		if (x == 0) 
			return 180.f;
		
		if (x > 0) 
			return atanf(y / x) * 180.f / spic::internal::defaults::PI + 90.f;
		
		return atanf(y / x) * 180.f / spic::internal::defaults::PI - 90.f;
	}

	void Point::Truncate(float max)
	{
		if (this->Length() > max)
		{
			this->Normalize();

			*this *= max;
		}
	}

	bool Point::Accumulate(Point& force, const float maxForce)
	{
		const float forceSoFar = Length();
		// Calculate how much force remains to be used
		const float forceRemaining = maxForce - forceSoFar;
		// Return false if there is no more force left to use
		if (forceRemaining <= 0.0) return false;
		// Calculate the force to add with the force we want to add
		const float forceToAdd = force.Length();
		// If the forceToAdd is lower then forceRemaining. Add all forceToAdd, 
		// otherwise add as much of the forceToAdd vector without goinger of the remaining force.
		
		if (forceToAdd >= forceRemaining)
		{
			force.Normalize();
			force *= forceRemaining;
			this->x += force.x;
			this->y += force.y;
			return false;
		}
		//add the remaining force
		this->x += force.x;
		this->y += force.y;
		return true;
	}

	enum { clockwise = 1, anticlockwise = -1 };

	int Point::Sign(const Point& point) const
	{
		if (this->y * point.x > this->x * point.y)
			return anticlockwise;
		return clockwise;
	}

	Point Point::MidPoint(const Point& point) const
	{
		Point ret;
		ret.x = (this->x + point.x) / 2;
		ret.y = (this->y + point.y) / 2;
		return ret;
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
