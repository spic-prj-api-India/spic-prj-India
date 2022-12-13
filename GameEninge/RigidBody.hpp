#ifndef RIGIDBODY_H_
#define RIGIDBODY_H_

#include <iostream>
#include "GameObject.hpp"
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

    class GameObject;

    /**
     * @brief A component representing a rigid body.
     */
    class RigidBody : public Component {
        public:
            RigidBody(const float mass, const float gravityScale, const BodyType bodyType);

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
            void Mass(const float newMass);

            /**
             * @brief Set rigid body's gravity scale
             * @param newGravityScale The desired gravity scale
             * @spicapi
             */
            void GravityScale(const float newGravityScale);

            /**
             * @brief Set rigid body's body type
             * @param newBodyType The desired body type
             * @spicapi
             */
            void BodyType(const spic::BodyType newBodyType);

            /**
             * @brief Apply force to this rigid body.
             * @param forceDirection A point, used as a vector to indicate direction
             *        and magnitude of the force to be applied.
             * @spicapi
             */
            void AddForce(std::shared_ptr<spic::GameObject> entity, const Point& forceDirection);

        private:
            float mass;
            float gravityScale;
            spic::BodyType bodyType;
    };

}

#endif // RIGIDBODY_H_
