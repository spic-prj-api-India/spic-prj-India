#pragma once

#include <IMouseListener.hpp>
#pragma once

#include <IMouseListener.hpp>
#include "ForceDriven.hpp"

class FollowMouseListener : public spic::IMouseListener {
public:
    FollowMouseListener();

    void OnMouseMoved() override;
    void OnMouseClicked() override;
    void OnMousePressed() override;
    void OnMouseReleased() override;

    void AddFollower(std::shared_ptr<spic::ForceDriven> follower);
private:
    std::unique_ptr<spic::Point> target;
};