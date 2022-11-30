#ifndef BUTTONCLICKLISTENER_H_
#define BUTTONCLICKLISTENER_H_

#include "IMouseListener.hpp"
#include "Button.hpp"
#include <vector>

namespace spic::internal {
    class ButtonClickListener : public spic::IMouseListener {
    public:
        ButtonClickListener();

        void OnMouseMoved() override;
        void OnMouseClicked() override;
        void OnMousePressed() override;
        void OnMouseReleased() override;

        void SetButtons(const std::vector<std::shared_ptr<spic::Button>>& buttons);
    private:
        std::vector<std::shared_ptr<spic::Button>> buttons;
    };
}

#endif // BUTTONCLICKLISTENER_H_
