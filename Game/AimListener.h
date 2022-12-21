#pragma once

#include <IMouseListener.hpp>
#include "GameObject.hpp"
#include "FollowMouseListener.h"
#include <Text.hpp>

class AimListener : public spic::IMouseListener {
public:
    AimListener(const spic::GameObject* weapon, std::shared_ptr<spic::Text> counter);

    void OnMouseMoved() override;
    void OnMouseClicked() override;
    void OnMousePressed() override;
    void OnMouseReleased() override;

    void Shoot();

    void CheckLoseCondition();
private:
    const spic::GameObject* weapon;
    std::shared_ptr<spic::Text> counter;
    float& angle;
    int maxRockets;
    int rocketCount;
    bool sceneLoaded;
};