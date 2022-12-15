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

        /**
         * @return The collider width and height
         * @spicapi
        */
        virtual Point Size() const = 0;

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
        bool enabled;
    };
}

#endif // COLLIDER2D_H_
