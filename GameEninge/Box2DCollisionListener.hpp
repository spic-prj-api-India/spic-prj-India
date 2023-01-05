#ifndef BOX2DCOLLISIONLISTENER_H_
#define BOX2DCOLLISIONLISTENER_H_

#include <functional>
// Use to remove box2d warnings from error list
#include <codeanalysis\warnings.h>
#pragma warning( push )
#pragma warning ( disable : ALL_CODE_ANALYSIS_WARNINGS )
#include "box2d/box2d.h"
#pragma warning( pop )
#include "Collider.hpp"
#include "ICollisionListener.hpp"

/**
 * @brief Contains internal methods which are added to the public extensions
*/
namespace spic::internal::extensions 
{
    /**
    * @brief A listener that listens if an Box2D collides with another Box2D body
    */
    class Box2DCollisionListener : public b2ContactListener, public spic::extensions::ICollisionListener
    {
    public:
        Box2DCollisionListener();

        /**
         * @brief Constructor for all callback methods
         * @param enterCallback Callback that runs OnTriggerEnter2D in behaviour scripts of entity if entity enters collision.
         *			Format: [](const std::shared_ptr<spic::GameObject>&, const std::shared_ptr<spic::Collider>&){}
         * @param exitCallback Callback that runs OnTriggerExit2D in behaviour scripts of entity if entity exits collision.
         *			Format: [](const std::shared_ptr<spic::GameObject>&, const std::shared_ptr<spic::Collider>&){}
         * @param stayCallback  Callback that runs OnTriggerStay2D in behaviour scripts of entity if entity stays collision.
         *			Format: [](const std::shared_ptr<spic::GameObject>&, const std::shared_ptr<spic::Collider>&){}
        */
        Box2DCollisionListener(spic::extensions::CollisionCallback enterCallback,
            spic::extensions::CollisionCallback exitCallback,
            spic::extensions::CollisionCallback stayCallback);

        /**
        * @brief Is called when body collides with another body
        */
        virtual void BeginContact(b2Contact* contact);

        /**
        * @brief Is called when body is not colliding with another body anymore
        */
        virtual void EndContact(b2Contact* contact);

        /**
        * @brief Is called when body is still colliding with another body
        */
        virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);

        /**
        * @brief Is called when body has stopped colliding with another body
        */
        virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
    private:
        /**
         * @brief Format: [](const std::shared_ptr<spic::GameObject>&, const std::shared_ptr<spic::Collider>&){}
        */
        spic::extensions::CollisionCallback onEnterCallback;
        /**
         * @brief Format: [](const std::shared_ptr<spic::GameObject>&, const std::shared_ptr<spic::Collider>&){}
        */
        spic::extensions::CollisionCallback onExitCallback;
        /**
         * @brief Format: [](const std::shared_ptr<spic::GameObject>&, const std::shared_ptr<spic::Collider>&){}
        */
        spic::extensions::CollisionCallback onStayCallback;
    };
}

#endif // BOX2DCOLLISIONLISTENER_H_