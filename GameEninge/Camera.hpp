#ifndef CAMERA_H_
#define CAMERA_H_

#include "GameObject.hpp"
#include "Color.hpp"

namespace spic {

    //TODO retrive aspect width/height from renderer

    /**
     * @brief Class representing a point of view towards the game scene.
     * @spicapi
     */
    class Camera : public GameObject {
        public:
            Camera();

            /**
             * @brief Sets background color of Camera.
             * @param color Desired value.
             * @spicapi
             */
            void BackgroundColor(const Color& color);

            /**
             * @brief Returns background color of Camera.
             * @return spic::Color.
             * @spicapi
             */
            const Color BackgroundColor() const;

            /**
             * @brief Sets background image path of Camera.
             * @param imagePath Desired value.
             * @spicapi
             */
            void BackgroundImage(const std::string& imagePath);

            /**
             * @brief Returns background image path of Camera.
             * @return string.
             * @spicapi
             */
            const std::string BackgroundImage() const;

            const float AspectWidth() const;
            const float AspectHeight() const;
        private:
            Color backgroundColor;
            std::string backgroundImage;
            float aspectWidth;
            float aspectHeight;  
    };
}
#endif // CAMERA_H_