#ifndef BOX2DCOLLISIONLISTENER_H_
#define BOX2DCOLLISIONLISTENER_H_

#include <functional>
#pragma warning(push, 0)
#include "box2d/box2d.h"
#pragma warning(pop)
#include "Collider.hpp"
#include "GameObject.hpp"

class Box2DCollisionListener : public b2ContactListener
{
public:
    Box2DCollisionListener();
    Box2DCollisionListener(std::function<void(const std::shared_ptr<spic::GameObject>&, const std::shared_ptr<spic::Collider>&)> enterCallback,
        std::function<void(const std::shared_ptr<spic::GameObject>&, const std::shared_ptr<spic::Collider>&)> exitCallback,
        std::function<void(const std::shared_ptr<spic::GameObject>&, const std::shared_ptr<spic::Collider>&)> stayCallback);

    virtual void BeginContact(b2Contact* contact);
    virtual void EndContact(b2Contact* contact);
    virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
    virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
private:
    std::function<void(const std::shared_ptr<spic::GameObject>&, const std::shared_ptr<spic::Collider>&)> onEnterCallback;
    std::function<void(const std::shared_ptr<spic::GameObject>&, const std::shared_ptr<spic::Collider>&)> onExitCallback;
    std::function<void(const std::shared_ptr<spic::GameObject>&, const std::shared_ptr<spic::Collider>&)> onStayCallback;
};

#endif // BOX2DCOLLISIONLISTENER_H_