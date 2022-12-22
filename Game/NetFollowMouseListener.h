#pragma once

#include <IMouseListener.hpp>
#include "Point.hpp"

class NetFollowMouseListener : public spic::IMouseListener {
public:
    NetFollowMouseListener(spic::Point& targetPosition);

    void OnMouseMoved() override;
    void OnMouseClicked() override;
    void OnMousePressed() override;
    void OnMouseReleased() override;
private:
    spic::Point& target;
};