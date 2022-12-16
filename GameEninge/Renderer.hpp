#ifndef RENDERING_H_
#define RENDERING_H_

#include "Transform.hpp"
#include "Animator.hpp"
#include "Text.hpp"
#include "Scene.hpp"
#include "Rect.hpp"

namespace spic::internal {

    struct Rendering
    {        
        /**
         * @brief Starts up a window with all the correct values
        */
        static void Start();

        /**
         * @brief Closes the window
        */
        static void Exit();
        
        /**
         * @brief Draws an gameobject
         * @details If the gameobject is inhertend from uiobject it will draw it on the internal window object(currently aspectwidth/height only does something for Text)
         * @param gameObject 
        */
        static void Draw(GameObject* gameObject);
        
        /**
         * @brief Updates the internal rendering camera and the internal background color
         * @param camera 
        */
        static void UpdateCamera(Camera* camera);

        /**
         * @brief Draws an rectangle in window space
         * @param rect The x, y, width, height of rectangle
         * @param angle The angle of the square
         * @param colour The colour of the square
        */
        static void DrawRect(const spic::Rect& rect, const double angle, const spic::Color& color);

        /**
         * @brief Draws an circle in window space
                    using the mid point circle algorithm https://en.wikipedia.org/w/index.php?title=Midpoint_circle_algorithm
         * @param center The center of the circle
         * @param angle The radius of the circle
         * @param pixelGap The gap (in pixels) between each point in the circle
         * @param color The color of the circle
        */
        static void DrawCircle(const spic::Point& center, const float radius, const spic::Color& color, const float pixelGap = 1.0f);

        /**
         * @brief Draws a point in window space
         * @param point Point to be drawn
         * @param color The color of the point
        */
        static void DrawPoint(const spic::Point& point, const spic::Color& color);

        /**
         * @brief Draws a line from start to end
         * @param start Start point of the line
         * @param end End point of the line
         * @param color Color of this line
        */
        static void DrawLine(const spic::Point& start, const spic::Point& end, const spic::Color& color);
        
        /**
         * @brief Draws a sprite as an ui object
         * @details Used for debugging
         * @param position The coordinates of the UI
         * @param sprite The sprite to Draw
        */
        static void DrawSprite(const Transform* position, Sprite* sprite);
        
        /**
         * @brief Cleans the frame
         * @details Needs to be called at the beginning of a frame
        */
        static void Clean();
        
        /**
         * @brief Cleans all stored values
         * @details Recommanded to be called at loading a new scene
        */
        static void NewScene();
        
        /**
         * @brief Renders all bufferd entities
        */
        static void Render();

        
        /**
         * @brief Gets the aspect values from the window
         * @details TODO add functionality
         * @return Width, Height
        */
        static std::pair<float, float> GetAspects();

        /**
         * @brief Draws the fps counter
        */
        static void DrawFps();
    };
}
#endif