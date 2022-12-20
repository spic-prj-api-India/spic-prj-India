#ifndef BEHAVIOURSCRIPT_H_
#define BEHAVIOURSCRIPT_H_

#include <iostream>
#include "Component.hpp"
#include "Collider.hpp"

namespace spic 
{
    /**
     * @brief Contains the beheviours of an object
     * @details Onupdate is used for code that should run every second. 
     *      OnInput is for behaviour based on the input
    */
    class BehaviourScript : public Component 
    {
        public:
            /**
             * @brief Is called once on the start of a new scene
             * @spicapi
             */
            virtual void OnStart();

            /**
             * @brief Is called every game tick
             * @spicapi
             */
            virtual void OnUpdate();

            /**
             * @brief Is called every input event
             * @sharedapi
             */
            virtual void OnInput();

            /**
             * @brief Sent when another object enters a trigger collider
             *        attached to this object (2D physics only).
             * @spicapi
             */
            virtual void OnTriggerEnter2D(const Collider& collider);

            /**
             * @brief Sent when another object leaves a trigger collider
             *        attached to this object (2D physics only).
             * @spicapi
             */
            virtual void OnTriggerExit2D(const Collider& collider);

            /**
             * @brief Sent each frame where another object is within a trigger
             *        collider attached to this object (2D physics only).
             * @spicapi
             */
            virtual void OnTriggerStay2D(const Collider& collider);
    };
}

#endif // BEHAVIOURSCRIPT_H_