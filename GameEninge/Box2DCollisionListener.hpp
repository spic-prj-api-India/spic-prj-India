#pragma once
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
        std::function<void(const std::shared_ptr<spic::GameObject>&, const std::shared_ptr<spic::Collider>&)> exitCallback);
    void BeginContact(b2Contact* contact);

    void EndContact(b2Contact* contact);
private:
    std::function<void(const std::shared_ptr<spic::GameObject>&, const std::shared_ptr<spic::Collider>&)> onEnterCallback;
    std::function<void(const std::shared_ptr<spic::GameObject>&, const std::shared_ptr<spic::Collider>&)> onExitCallback;
};