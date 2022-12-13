#ifndef BOXCOLLIDER_H_
#define BOXCOLLIDER_H_

#include "Collider.hpp"

namespace spic {

    /**
     * @brief A collider which represents a rectangular collision area.
     */
    class BoxCollider : public Collider {
        public:
            BoxCollider();

            /**
             * @brief The collider's width
             * @return The current width
             * @spicapi
             */
            float Width() const;

            /**
             * @brief The collider's width
             * @param newWidth The desired width
             * @spicapi
             */
            void Width(const float newWidth);

            /**
             * @brief The collider's height
             * @return The current height
             * @spicapi
             */
            float Height() const;

            /**
             * @brief The collider's height
             * @param newHeight The desired height
             * @spicapi
             */
            void Height(const float newHeight);

        private:
            float width;
            float height;
    };

}

#endif // BOXCOLLIDER_H_
