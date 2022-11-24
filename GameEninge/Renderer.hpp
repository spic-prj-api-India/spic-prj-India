#ifndef RENDERING_H_
#define RENDERING_H_

#include "Transform.hpp"
#include "Animator.hpp"
#include "Text.hpp"
#include "Scene.hpp"
#include "WindowValues.hpp"

namespace spic::internal {

    struct Rendering
    {
        /// @brief Starts up a window with all the correct values
        /// @param values 
        static void Start(const spic::window::WindowValues* values);

        /// @brief Closes the window
        static void Exit();

        /// @brief Draws an gameobject
        /// @details If the gameobject is inhertend from uiobject it will draw it on the internal window object(currently aspectwidth/height only does something for Text)
        /// @param gameObject 
        static void Draw(GameObject* gameObject);

        /// @brief Updates the internal rendering camera and the internal background color
        /// @param camera 
        static void UpdateCamera(Camera* camera);

        /// @brief Sets the background color to internal one (needs to be called every frame)
        static void SetBackgroundColor();

        /// @brief Draws a line from start to end
        /// @param start Start point of the line
        /// @param end End point of the line
        /// @param colour Color of this line
        static void DrawLine(const Point* start, const Point* end, const Color* color);

        /// @brief Draws a sprite as an ui object
        /// @details Used for debugging
        /// @param position The coridatnes are for the UI 
        /// @param sprite The sprite to Draw
        static void DrawSprite(const Transform* position,const bool isUi, Sprite* sprite);

        /// @brief Draws a animator as an ui object
        /// @details Used for debugging
        /// @param position The coridatnes are for the UI 
        /// @param animator The animator to Draw
        static void DrawAnimator(const Transform* position, const bool isUi, Animator* animator);

        /// @brief Draws only the text of the Text object
        /// @param text Text object needs to have a valid Transform
        static void DrawText(Text* text, const bool isUi);

        /// @brief Cleans the frame
        /// @details Needs to be called at the beginning of a frame
        static void Clean();

        /// @brief Cleans all stored values
        /// @details Recommanded to be called at loading a new scene
        static void NewScene();

        /// @brief Renders all bufferd
        static void Render();

        /// @brief Gets the aspect values from the window
        /// @details TODO add functionality
        /// @return Width, Height
        static std::pair<float, float> GetAspects();
    };
}
#endif