#pragma once

#include <IMouseListener.hpp>
#include "GameObject.hpp"
#include "FollowMouseListener.h"

class AimListener : public spic::IMouseListener {
public:
    AimListener(const spic::GameObject* weapon);

    void OnMouseMoved() override;
    void OnMouseClicked() override;
    void OnMousePressed() override;
    void OnMouseReleased() override;

    void Shoot();

    void CheckLoseCondition();
private:
    const spic::GameObject* weapon;
    float& angle;
    int maxRockets;
    int rocketCount;
    bool sceneLoaded;
};