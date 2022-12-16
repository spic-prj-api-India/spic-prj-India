#ifndef DEBUG_H_
#define DEBUG_H_

#include "Point.hpp"
#include "Color.hpp"
#include <string>

namespace spic {
    /**
     * @brief Some convenient debugging functions.
     */
    namespace Debug {
        /*
        * @brief Sets DEBUG_MODE to true if project is running in Debug mode.
        */
        #ifdef NDEBUG
            const inline bool DEBUG_MODE = false;
        #else
            const inline bool DEBUG_MODE = true;
        #endif

        /*
         * @brief Enables or disables collider visibility.
        */
        inline bool COLLIDER_VISIBILITY = false;

        /**
         * @brief Draws a colored line between specified start and end points.
         * @param start The starting point.
         * @param end The end point.
         * @param color The line color, defaults to white.
         * @spicapi
         */
        void DrawLine(const Point& start, const Point& end, const Color& color = Color::white());

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

}

#endif // DEBUG_H_
