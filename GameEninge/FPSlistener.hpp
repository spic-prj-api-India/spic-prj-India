#pragma once

#include "IKeyListener.hpp"

class FPSListener : public spic::IKeyListener {
    void OnKeyPressed() override;
    void OnKeyReleased() override;

public:
    static bool renderFps;
};