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

		float Length() const;

		float Normalize();

		float Distance(const Point& point) const;

		Point Side() const;

		float Rotation() const;

		bool Accumulate(Point& point, const float maxForce);

		/**
		 * @brief operator for adding Point
		 * @param point Point that will be added
		 * @return spic::Point
		*/
		Point operator +(const Point& point);

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
		Point operator -(const Point& point);

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
		Point operator *(const Point& point);

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
		Point operator /(const Point& point);

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
		Point operator +(const float value);

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
		Point operator -(const float value);

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
		Point operator *(const float value);

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
		Point operator /(const float value);

		/**
		 * @brief operator for dividing Point
		 * @param value Value used as divider
		*/
		void operator /=(const float value);

		float DotProduct(const Point& point);
	};
}

#endif // POINT_H_
