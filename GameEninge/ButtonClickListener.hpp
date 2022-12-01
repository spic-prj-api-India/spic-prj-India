#ifndef BUTTONCLICKLISTENER_H_
#define BUTTONCLICKLISTENER_H_

#include "IMouseListener.hpp"
#include "Button.hpp"
#include <vector>

namespace spic::internal {
    /**
       * @brief Listens to Button click, when button is clicked. 
       *        method "Click" of Button is called.
    */
    class ButtonClickListener : public spic::IMouseListener {
    public:
        ButtonClickListener();

        void OnMouseMoved() override;
        void OnMouseClicked() override;
        void OnMousePressed() override;
        void OnMouseReleased() override;

        /**
        * @brief Sets buttons of listener.
        * @param buttons Active buttons in scene.
        * @spicapi
        */
        void SetButtons(const std::vector<std::shared_ptr<spic::Button>>& buttons);
    private:
        std::vector<std::shared_ptr<spic::Button>> buttons;
    };
}

#endif // BUTTONCLICKLISTENER_H_
