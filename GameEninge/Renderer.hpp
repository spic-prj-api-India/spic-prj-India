#ifndef RENDERING_H_
#define RENDERING_H_

#include "Transform.hpp"
#include "Animator.hpp"
#include "Text.hpp"
#include "Scene.hpp"
#include "Rect.hpp"
#include "Circle.hpp"
#include "Line.hpp"

namespace spic::internal 
{

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
         * @brief Add debug line to renderer, line will be drawn at the end of the render in world space.
         * @details Line is not drawn when line is not in camera view.
         * @param line Line that will be drawn
         * @param color Color of this line
        */
        static void AddDebugLine(const spic::Line& line, const spic::Color& color);

        /**
         * @brief Add debug rectangle to renderer, rectangle will be drawn at the end of the render in world space.
         * @details Rectangle is not drawn when rectangle is not in camera view.
         * @param rect Rectangle that will be drawn
         * @param color Color of this line
        */
        static void AddDebugRect(const spic::Rect& rect, const double angle, const spic::Color& color);

        /**
         * @brief Add debug circle to renderer, circle will be drawn at the end of the render in world space.
         * @details Circle is not drawn when circle is not in camera view.
         * @param circle Circle that will be drawn
         * @param pixelGap The gap (in pixels) between each point in the circle
         * @param color Color of this line
        */
        static void AddDebugCircle(const spic::Circle& circle, const spic::Color& color, const float pixelGap = 1.0f);

        /**
         * @brief Add debug point to renderer, point will be drawn at the end of the render in world space.
         * @details Point is not drawn when point is not in camera view.
         * @param point Point that will be drawn
         * @param color Color of this line
        */
        static void AddDebugPoint(const spic::Point& point, const spic::Color& color);

        /**
         * @brief Draws all added debug shapes
         * @details Shapes are not drawn when rectangle is not in camera view.
        */
        static void DrawDebugShapes();
        
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
         * @brief Renders all buffered entities
		 * @details Debug shapes will be reset in this function
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