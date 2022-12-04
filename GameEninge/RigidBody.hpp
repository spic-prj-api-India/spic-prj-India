#ifndef RIGIDBODY_H_
#define RIGIDBODY_H_

#include <iostream>
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

            /**
             * @brief Get rigid body's mass
             * @return The current mass
             * @spicapi
             */
            float Mass() const;

            /**
             * @brief Get rigid body's gravity scale
             * @return The current gravity scale
             * @spicapi
             */
            float GravityScale() const;

            /**
             * @brief Get rigid body's velocity
             * @return The current velocity
             * @spicapi
             */
            Point Velocity() const;

            /**
             * @brief Get rigid body's body type
             * @return The current body type
             * @spicapi
             */
            BodyType BodyType() const;

            /**
             * @brief Set rigid body's body mass
             * @param newMass The desired mass
             * @spicapi
             */
            void Mass(float newMass);

            /**
             * @brief Set rigid body's gravity scale
             * @param newGravityScale The desired gravity scale
             * @spicapi
             */
            void GravityScale(float newGravityScale);

            /**
             * @brief Set rigid body's body type
             * @param newBodyType The desired body type
             * @spicapi
             */
            void BodyType(spic::BodyType newBodyType);

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
            spic::BodyType bodyType;
    };

}

#endif // RIGIDBODY_H_
