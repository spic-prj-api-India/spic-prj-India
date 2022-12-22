#pragma once

#include <IMouseListener.hpp>
#include "Point.hpp"

class FollowMouseListener : public spic::IMouseListener {
public:
    FollowMouseListener(spic::Point& targetPosition);

    void OnMouseMoved() override;
    void OnMouseClicked() override;
    void OnMousePressed() override;
    void OnMouseReleased() override;
private:
    spic::Point& target;
};