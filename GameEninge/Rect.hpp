#ifndef RECT_H_
#define RECT_H_

namespace spic {
	/**
	* @brief A rectangle, with the origin at the upper left (floating point).
	*/
	struct Rect
	{
		/**
		* @brief Upper left x of rectangle
		*/
		float x;

		/**
		* @brief Upper left y of rectangle
		*/
		float y;

		/**
		* @brief Width of rectangle
		*/
		float w;

		/**
		* @brief Height of rectangle
		*/
		float h;
	};
}

#endif // RECT_H_
