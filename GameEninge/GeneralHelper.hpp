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
#include "NetworkPacket.hpp"
#include "Rect.hpp"

/**
 * @brief Contains helpfull preprogrammed functions
*/
namespace spic::helper_functions
{
	/**
	 * @brief Contains functions which are general helpfull
	*/
	namespace general_helper
	{
		/**
		 * @brief Rotate point p on point org by the radians contained in angle
		 * @param org The point to rotate around
		 * @param angle The angle to rotate (in radians)
		 * @param p Point that rotates
		*/
		void RotatePoint(const Point& org, float angle, Point& p) noexcept;
		
		/**
		 * @brief Gets an random unique uuid
		 * @return An unique uuid
		*/
		std::string GetRandomUUID();

		/**
		 * @brief Sorts sprite based on order layer first and sorting layer second
		 * @param a Sprite A
		 * @param b Sprite B
		 * @return If sprites need to be swapped
		*/
		bool SpriteSorting(const std::shared_ptr<Sprite> a, const std::shared_ptr<Sprite> b);

		/**
		 * @brief Sorts network packages based on timing
		 * @param a NetworkPacket a
		 * @param b NetworkPacket b
		 * @return If the packets need to be swapped
		*/
		bool NetworkPacketSorting(const spic::NetworkPacket& a, const spic::NetworkPacket& b);

		/**
		 * @brief Gets all corner rectangle points (with rotation based on center of rectangle)
		 * @param orgin The left upper corner
		 * @param angle The amount of radians to rotate
		 * @param aspectWidth The width of the rectangle
		 * @param aspectHeight The height of the rectangle
		 * @return An array with all 4 corner points of a rectangle
		*/
		std::array<Point, 4> GetPoints(const Point& origin, const float angle, const float aspectWidth, const float aspectHeight);
		
		/**
		 * @brief Calculates if a point is within a square (https://math.stackexchange.com/a/190373)
		 * @param point The point to check
		 * @param square A rectangle (can be obtained by GetPoints)
		 * @return If the point is in the square
		*/
		bool CalculateWithinSquare(const Point& point, std::array<Point, 4>& square);

		/**
		 * @brief Calculates if two rects intersect with eachother
		 * @param rect1 Rectangle to check
		 * @param rect2 Rectangle to check
		 * @return If it intersects with each other
		*/
		bool RectIntersection(const Rect& rect1, const Rect& rect2);

		/**
		 * @brief Calculates if a line intersects with another line.
		 *		Sets intersection point and distance to intersection if intersection exists.
		 * @param sPoint1 Start point of line 1
		 * @param ePoint1 End point of line 1
		 * @param sPoint2 Start point of line 2
		 * @param ePoint2 End point of line 2
		 * @param intersectPoint Intersection point, is reference so that intersect point can be used outside function
		 * @param distance Distance to intersection, is reference so that distance between lines can be used outside function
		 * @return
		*/
		bool LineIntersection(const Point& sPoint1, const Point& ePoint1, const Point& sPoint2, const Point& ePoint2, Point& intersectPoint, float& distance);
		
		/**
		 * @brief Gets the center of a rectangle based on the size of the rectangle and the left upper corner (no rotation)
		 * @param point The upper left corner
		 * @param aspectWidth The width of the rectangle
		 * @param aspectHeight The height of the rectangle
		 * @return The center point
		*/
		Point GetCenter(const Point& point, const float aspectWidth, const float aspectHeight);
		
		/**
		 * @brief Precision rounds an floating value to an int
		 * @tparam T An floating value
		 * @param t The value
		 * @return Casted to int
		*/
		template <class T>
		int PrecisionRoundingoInt(T t)
		{
			return static_cast<int>(std::lround(t));
		}

		/**
		 * @brief Convert a degree to radians
		 * @tparam T The return type
		 * @tparam R Any primitive which can contain degrees
		 * @param DEG The amount of degrees
		 * @return The converted radians
		*/
		template <typename T, typename D>
		T DEG2RAD(D DEG)
		{
			return static_cast<T>(DEG * M_PI / 180.0);
		}

		/**
		 * @brief Convert radians to a degree
		 * @tparam T A value which can contain degrees
		 * @tparam R An floating type primitive
		 * @param RAD The amount of radians
		 * @return The converted degrees
		*/
		template <typename T, typename R>
		T RAD2DEG(R RAD)
		{
			return static_cast<T>(RAD * 180.0 / M_PI);
		}
	}
}
#endif