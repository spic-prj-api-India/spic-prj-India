#include "Box2DCollisionListener.hpp"

Box2DCollisionListener::Box2DCollisionListener() {

}
Box2DCollisionListener::Box2DCollisionListener(std::function<void(const std::shared_ptr<spic::GameObject>&, const std::shared_ptr<spic::Collider>&)> enterCallback,
    std::function<void(const std::shared_ptr<spic::GameObject>&, const std::shared_ptr<spic::Collider>&)> exitCallback) {
    onEnterCallback = enterCallback;
    onExitCallback = exitCallback;
}
void Box2DCollisionListener::BeginContact(b2Contact* contact) {
    // Check if fixture A is a entity
    uintptr_t bodyData = contact->GetFixtureA()->GetBody()->GetUserData().pointer;
    if (bodyData) {
        spic::GameObject* entity = reinterpret_cast<spic::GameObject*>(bodyData);
        std::shared_ptr<spic::GameObject> sharedPtr = std::make_shared<spic::GameObject>(*entity);
        std::shared_ptr<spic::Collider> collider = entity->GetComponent<spic::Collider>();
        onEnterCallback(sharedPtr, collider);
    }
    // Check if fixture B is a entity
    bodyData = contact->GetFixtureB()->GetBody()->GetUserData().pointer;
    if (bodyData) {
        spic::GameObject* entity = reinterpret_cast<spic::GameObject*>(bodyData);
        std::shared_ptr<spic::GameObject> sharedPtr = std::make_shared<spic::GameObject>(*entity);
        std::shared_ptr<spic::Collider> collider = entity->GetComponent<spic::Collider>();
        onEnterCallback(sharedPtr, collider);
    }
}

void Box2DCollisionListener::EndContact(b2Contact* contact) {
    //// Check if fixture A is a entity
    //uintptr_t bodyData = contact->GetFixtureA()->GetBody()->GetUserData().pointer;
    //if (bodyData) {
    //    spic::GameObject* entity = reinterpret_cast<spic::GameObject*>(bodyData);
    //    std::shared_ptr<spic::GameObject> sharedPtr = std::make_shared<spic::GameObject>(entity);
    //    std::shared_ptr<spic::Collider> collider = entity->GetComponent<spic::Collider>();
    //    onExitCallback(sharedPtr, collider);
    //}
    //// Check if fixture B is a entity
    //bodyData = contact->GetFixtureB()->GetBody()->GetUserData().pointer;
    //if (bodyData) {
    //    spic::GameObject* entity = reinterpret_cast<spic::GameObject*>(bodyData);
    //    std::shared_ptr<spic::GameObject> sharedPtr = std::make_shared<spic::GameObject>(entity);
    //    std::shared_ptr<spic::Collider> collider = entity->GetComponent<spic::Collider>();
    //    onExitCallback(sharedPtr, collider);
    //}
}