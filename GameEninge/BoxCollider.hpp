#ifndef BOXCOLLIDER_H_
#define BOXCOLLIDER_H_

#include "Collider.hpp"

namespace spic {
    /**
     * @brief A collider which represents a rectangular collision area.
     */
    class BoxCollider : public Collider {
        public:
            /**
             * @brief Default constructor
             */
            BoxCollider();

            /*
            * @brief Sets width and height of collider
            * @throws Throws if width or height is below zero
            */
            BoxCollider(const float width, const float height);

            /**
             * @return The collider's width and height
             * @spicapi
             */
            virtual Point Size() const override;

            /**
             * @brief The collider's width
             * @return The current width
             * @spicapi
             */
            float Width() const;

            /**
             * @brief The collider's width
             * @param newWidth The desired width
             * @throws Throws if newWidth is below zero
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
             * @throws Throws if newHeight is below zero
             * @spicapi
             */
            void Height(const float newHeight);

        private:
            float width;
            float height;
    };

}

#endif // BOXCOLLIDER_H_
