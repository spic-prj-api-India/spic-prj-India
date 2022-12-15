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
        virtual Point Size() const = 0;
        bool Enabled() const;
        void Disable();
        void Enable();
    private:
        bool enabled;
    };
}

#endif // COLLIDER2D_H_
