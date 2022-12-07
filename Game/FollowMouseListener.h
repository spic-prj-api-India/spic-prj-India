#pragma once

#include <IMouseListener.hpp>
#include "Flock.hpp"

class FollowMouseListener : public spic::IMouseListener {
public:
    FollowMouseListener();

    void OnMouseMoved() override;
    void OnMouseClicked() override;
    void OnMousePressed() override;
    void OnMouseReleased() override;

    void AddFollower(const std::shared_ptr<spic::Flock>& follower);
private:
    std::vector<std::shared_ptr<spic::Flock>> followers;
};