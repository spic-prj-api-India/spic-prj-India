#pragma once

#include <IKeyListener.hpp>

class KeyListener : public spic::IKeyListener {
    void OnKeyPressed() override;
    void OnKeyReleased() override;
};