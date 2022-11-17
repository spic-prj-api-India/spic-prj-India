#pragma once

#include <IMouseListener.hpp>

class MouseListener : public spic::IMouseListener {
    void OnMouseMoved() override;
    void OnMouseClicked() override;
    void OnMousePressed() override;
    void OnMouseReleased() override;
};