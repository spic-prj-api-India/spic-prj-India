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

            void BackgroundColor(const Color& color);
            const Color BackgroundColor();

            const float AspectWidth();
            const float AspectHeight();

        private:
            Color backgroundColor;
            float aspectWidth;
            float aspectHeight;
        
    };

}

#endif // CAMERA_H_
