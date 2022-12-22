#pragma once

#include <IMouseListener.hpp>
#include "GameObject.hpp"
#include "FollowMouseListener.h"

class AimListener : public spic::IMouseListener {
public:
    AimListener(std::shared_ptr<spic::GameObject> weapon);

    void OnMouseMoved() override;
    void OnMouseClicked() override;
    void OnMousePressed() override;
    void OnMouseReleased() override;

    void Shoot();
private:
    std::shared_ptr<FollowMouseListener> followMouseListener;
    std::shared_ptr<spic::GameObject> weapon;
    float angle;
    int rocketCount;
};