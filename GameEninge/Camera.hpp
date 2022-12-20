#ifndef CAMERA_H_
#define CAMERA_H_

#include "GameObject.hpp"
#include "Color.hpp"

namespace spic 
{
    /**
     * @brief Class representing a point of view towards the game scene.
     * @details Currently aspectWidth and aspectWidth returns the same width
            and height as what is in the settings namespace.
     * @spicapi
     */
    class Camera : public GameObject 
    {
        public:
            Camera();

            /**
             * @brief Sets background color of Camera.
             * @param color Desired value.
             * @sharedapi
             */
            void BackgroundColor(const Color& color);

            /**
             * @brief Returns background color of Camera.
             * @return spic::Color.
             * @sharedapi
             */
            const Color BackgroundColor() const;

            /**
             * @brief Sets background image path of Camera.
             * @param imagePath Desired value.
             * @sharedapi
             */
            void BackgroundImage(const std::string& imagePath);

            /**
             * @brief Returns background image path of Camera.
             * @return string.
             * @sharedapi
             */
            const std::string BackgroundImage() const;
            
            /**
             * @brief Getter
             * @return Gets the aspect width of the camera
            */
            const float AspectWidth() const;

            /**
             * @brief Getter
             * @return Gets the aspect width of the camera
            */
            const float AspectHeight() const;
        private:
            /**
             * @brief The current color of the background 
             * @spicapi
            */
            Color backgroundColor;

            /**
             * @brief The current image of the background
             * @sharedapi
            */
            std::string backgroundImage;

            /**
             * @brief The current width of the camera
             * @sharedapi
            */
            float aspectWidth;

            /**
             * @brief The current height of the camera
             * @sharedapi
            */
            float aspectHeight;  
    };
}
#endif // CAMERA_H_