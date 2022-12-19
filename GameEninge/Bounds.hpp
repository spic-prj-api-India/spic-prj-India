#include "Point.hpp"
#ifndef BOUNDS_H_
#define BOUNDS_H_

namespace spic {
	/**
	 * @brief Bounds is a defined area with a width, height, top, bottom, right and left.
	 *			Which can used to define an area where an entity must stay in. 
	 *			This is used for wall avoidance.
	*/
	class Bounds {
	public:
		/**
		 * @brief Set all variables to 0.0f.
		 */
		Bounds();

		/**
		 * @brief Sets bounds from { 0.0f, 0.0f } to { v.x, v.y }.
		*/
		Bounds(const Point& v);

		/**
		 * @brief Sets bounds with parameters.
		 * @param x X of bounds.
		 * @param y Y of bounds.
		 * @param w W of bounds.
		 * @param h H of bounds.
		*/
		Bounds(const float x, const float y, const float w, const float h);

		/**
		 * @brief Returns width of Bounds.
		 * @return float.
		*/
		float Width() const;

		/**
		 * @brief Returns height of Bounds.
		 * @return float.
		*/
		float Height() const;

		/**
		 * @brief Returns top of Bounds.
		 * @return float.
		*/
		float Top() const;

		/**
		 * @brief Returns bottom of Bounds.
		 * @return float.
		*/
		float Bottom() const;

		/**
		 * @brief Returns left of Bounds.
		 * @return float.
		*/
		float Left() const;

		/**
		 * @brief Returns right of Bounds.
		 * @return float.
		*/
		float Right() const;

		/**
		 * @brief Checks if point is in bounds.
		 * @param point Point that is being checked.
		 * @return bool.
		*/
		bool InBounds(Point point) const;
	private:
		float width;
		float height;
		float top;
		float bottom;
		float right;
		float left;
	};
}

#endif // BOUNDS_H_