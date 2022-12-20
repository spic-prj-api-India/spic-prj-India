#ifndef DEBUG_H_
#define DEBUG_H_

#include "Point.hpp"
#include "Rect.hpp"
#include "Circle.hpp"
#include "Color.hpp"
#include <string>

/**
 * @brief Some convenient debugging functions. Function are only run in Debug mode.
*/
namespace spic::debug {
    /*
    * @brief Sets DEBUG_MODE to true if project is running in Debug mode.
    */
    #ifdef NDEBUG
        const inline bool DEBUG_MODE = false;
    #else
        const inline bool DEBUG_MODE = true;
    #endif

    /**
    * @brief Draws a colored line between specified start and end points in world space.
    * @details Line is not drawn when line is not in camera view.
    * @param start The starting point.
    * @param end The end point.
    * @param color The line color, defaults to white.
    * @spicapi
    */
    void DrawLine(const Point& start, const Point& end, const Color& color = Color::white());

    /**
    * @brief Draws a colored rectangle with a specified angle in world space.
    * @details Rectangle is not drawn when rectangle is not in camera view.
    * @param rect The rectangle.
    * @param angle The angle of the rectangle in radians.
    * @param color The rectangle color, defaults to white.
    * @sharedapi
    */
    void DrawRect(const Rect& rect, const double angle, const Color& color = Color::white());

    /**
    * @brief Draws a colored circle in world space.
    * @details Circle is not drawn when circle is not in camera view.
    * @param circle The circle.
    * @param color The circle color, defaults to white.
    * @param pixelGap The gap (in pixels) between each point in the circle
    * @sharedapi
    */
    void DrawCircle(const Circle& circle, const Color& color = Color::white(), const float pixelGap = 1.0f);

    /**
    * @brief Draws a colored point in world space.
    * @details Point is not drawn when point is not in camera view.
    * @param point The point.
    * @param color The line color, defaults to white.
    * @sharedapi
    */
    void DrawPoint(const spic::Point& point, const spic::Color& color);

    /**
    * @brief Logs a message to the Console.
    * @param message The message to write.
    * @spicapi
    */
    void Log(const std::string& message);

    /**
    * @brief A variant of Debug.Log that logs an error message to the console.
    * @param message The message to write.
    * @spicapi
    */
    void LogError(const std::string& error);

    /**
    * @brief A variant of Debug.Log that logs a warning message to the console.
    * @param message The message to write.
    * @spicapi
    */
    void LogWarning(const std::string& warning);
}

#endif // DEBUG_H_