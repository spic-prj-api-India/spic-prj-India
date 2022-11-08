#ifndef RIGIDBODY_H_
#define RIGIDBODY_H_

#include "Component.hpp"
#include "Point.hpp"

namespace spic {

    /**
     * @brief Enumeration for different rigid body types
     */
    enum class BodyType {
        staticBody,
        kinematicBody,
        dynamicBody
    };

    /**
     * @brief A component representing a rigid body.
     */
    class RigidBody : public Component {
        public:
            RigidBody(float mass, float gravityScale, BodyType bodyType);
            float GetMass() const;
            float GetGravityScale() const;
            BodyType GetBodyType() const;

            /**
             * @brief Apply force to this rigid body.
             * @param forceDirection A point, used as a vector to indicate direction
             *        and magnitude of the force to be applied.
             * @spicapi
             */
            void AddForce(const Point& forceDirection);

        private:
            float mass;
            float gravityScale;
            BodyType bodyType;
    };

}

#endif // RIGIDBODY_H_
