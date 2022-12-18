#ifndef COLLIDER2D_H_
#define COLLIDER2D_H_

#include "Component.hpp"

namespace spic {
    /**
     * @brief The base class for all colliders.
     * @spicapi
     */
    class Collider : public Component {
    public:
        Collider();
        Collider(const float friction, const float bounciness);

        /**
         * @return The collider width and height
         * @spicapi
        */
        virtual Point Size() const = 0;

        /**
       * @brief Get the collider's bounciness
       * @return The bounciness
       * @spicapi
       */
        float Bounciness() const;

        /**
         * @brief Set the collider's bounciness
         * @param newBounciness The desired bounciness
         * @throws Throws if newBounciness is not between 0 or 1
         * @spicapi
         */
        void Bounciness(const float newBounciness);

        /**
        * @brief Get the collider's friction
        * @return The friction
        * @spicapi
        */
        float Friction() const;

        /**
         * @brief Set the collider's friction
         * @param newFriction The desired friction
         * @spicapi
         */
        void Friction(const float newFriction);

        /**
         * @brief Is collision detection enabled
         * @return The current enabled
         * @spicapi
        */
        bool Enabled() const;

        /**
         * @brief Disables collision detection
         * @spicapi
        */
        void Disable();

        /**
         * @brief Enables collision detection
         * @spicapi
        */
        void Enable();
    private:
        /**
        * @brief How bouncy is the surface? A value of 0 will not bounce. A value of 1 will bounce without any loss of energy.
        */
        float bounciness;

        /**
        * @brief The friction used when already moving. This value is usually between 0 and 1.
        */
        float friction;

        /**
        * @brief Variable sets if collision detection is enabled.
        */
        bool enabled;
    };
}

#endif // COLLIDER2D_H_
