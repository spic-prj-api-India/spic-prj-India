#ifndef CIRCLECOLLIDER_H_
#define CIRCLECOLLIDER_H_

#include "Collider.hpp"

namespace spic {
    /**
     * @brief A collider which represents a circular collision area.
     */
    class CircleCollider : public Collider {
        public:
            CircleCollider();

            /*
            * @brief Sets radius of collider
            */
            CircleCollider(const float radius);

            /**
             * @return The collider's width and height
             * @spicapi
             */
            virtual Point Size() const override;

            /**
             * @brief Get the collider's radius
             * @return The radius
             * @spicapi
             */
            float Radius() const;

            /**
             * @brief Set the collider's radius
             * @param newRadius The desired radius
             * @spicapi
             */
            void Radius(const float newRadius);

        private:
            float radius;
    };

}

#endif // CIRCLECOLLIDER_H_
