#pragma once

#include <IKeyListener.hpp>
#include "GameObject.hpp"
#include <Text.hpp>
#include <Input.hpp>

class InputTypeListener : public spic::IKeyListener {
public:
    InputTypeListener(std::shared_ptr<spic::Text> inputField, std::string& text);

    void OnKeyPressed() override;
    void OnKeyReleased() override;
private:
    std::shared_ptr<spic::Text> inputField;
    std::string& text;
    spic::input::KeyCode keyCode;
};