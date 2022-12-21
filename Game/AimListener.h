#pragma once

#include <IMouseListener.hpp>
#include "GameObject.hpp"
#include "FollowMouseListener.h"

class AimListener : public spic::IMouseListener {
public:
    AimListener(const std::string& entityName);

    void OnMouseMoved() override;
    void OnMouseClicked() override;
    void OnMousePressed() override;
    void OnMouseReleased() override;

    void Shoot();
private:
    std::shared_ptr<spic::GameObject> weapon;
    float angle;
    int rocketCount;
};