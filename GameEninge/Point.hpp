#ifndef POINT_H_
#define POINT_H_

namespace spic {
	/**
	 * @brief Struct representing both a 2D point and a 2D vector.
	 * @spicapi
	 */
	struct Point {
		float x = 0.0f;
		float y = 0.0f;

		/**
		 * @brief Returns the length of a 2D Vector.
		 * @return float
		*/
		float Length() const;

		/**
		 * @brief Returns the squared length of a 2D Vector.
		 * @return float
		*/
		float LengthSq() const;

		/**
		 * @brief Normalizes 2D Vector
		 * @return float Length.
		*/
		float Normalize();

		/**
		 * @brief Returns distance between to points.
		 * @return float
		*/
		float Distance(const Point& point) const;

		/**
		 * @brief Returns a 2D Vector perpendicular to this 2D Vector.
		 * @return spic::Point
		*/
		Point Perp() const;

		/**
		 * @brief Returns rotation of 2D Vector.
		 * @return float Rotation in degrees.
		*/
		float Rotation() const;

		/**
		 * @brief Checks if force can be added. 
		 *			If force added to current force is higher than maxForce, then only remaining force is added
		 * @param force Force that needs to be applied
		 * @param maxForce Max force that can be used
		 * @return bool Is true if force could be added, Is false when force couldn't be added
		*/
		bool Accumulate(Point& force, const float maxForce);

		/**
		 * @brief operator for adding Point
		 * @param point Point that will be added
		 * @return spic::Point
		*/
		Point operator +(const Point& point) const;

		/**
		 * @brief operator for adding Point
		 * @param point Point that will be added
		*/
		void operator +=(const Point& point);

		/**
		 * @brief operator for substracting Point
		 * @param point Point that will be substracted
		 * @return spic::Point
		*/
		Point operator -(const Point& point) const;

		/**
		 * @brief operator for substracting Point
		 * @param point Point that will be substracted
		*/
		void operator -=(const Point& point);

		/**
		 * @brief operator for multipling Point
		 * @param point Point used as multiplier
		 * @return spic::Point
		*/
		Point operator *(const Point& point) const;

		/**
		 * @brief operator for multipling Point
		 * @param point Point used as multiplier
		*/
		void operator *=(const Point& point);

		/**
		 * @brief operator for dividing Point
		 * @param point Point used as divider
		 * @return spic::Point
		*/
		Point operator /(const Point& point) const;

		/**
		 * @brief operator for dividing Point
		 * @param point Point used as divider
		*/
		void operator /=(const Point& point);

		/**
		 * @brief operator for adding Point
		 * @param value Value that will be added
		 * @return spic::Point
		*/
		Point operator +(const float value) const;

		/**
		 * @brief operator for adding Point
		 * @param value Value that will be added
		*/
		void operator +=(const float value);

		/**
		 * @brief operator for substracting Point
		 * @param value Value that will be substracted
		 * @return spic::Point
		*/
		Point operator -(const float value) const;

		/**
		 * @brief operator for substracting Point
		 * @param value Point that will be substracted
		*/
		void operator -=(const float value);

		/**
		 * @brief operator for multipling Point
		 * @param value Value used as multiplier
		 * @return spic::Point
		*/
		Point operator *(const float value) const;

		/**
		 * @brief operator for multipling Point
		 * @param value Value used as multiplier
		*/
		void operator *=(const float value);

		/**
		 * @brief operator for dividing Point
		 * @param value Value used as divider
		 * @return spic::Point
		*/
		Point operator /(const float value) const;

		/**
		 * @brief operator for dividing Point
		 * @param value Value used as divider
		*/
		void operator /=(const float value);

		/**
		 * @brief operator for checking if points are equal
		 * @param value Value used for checking
		*/
		bool operator==(const Point value) const;

		/**
		 * @brief operator for using Point as key in map
		 * @param cp Compare point
		*/
		bool operator<(const Point& cp) const noexcept;

		/**
		 * @brief operator for multipling Point
		 * @param point Point used as multiplier
		 * @return float
		*/
		float Dot(const Point& point) const;
	};
}

#endif // POINT_H_
