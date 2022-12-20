#ifndef BUTTONCLICKLISTENER_H_
#define BUTTONCLICKLISTENER_H_

#include "IMouseListener.hpp"
#include "Button.hpp"
#include <vector>

/**
 * @brief Contains internal button/mouse listeners and the input implementation
*/
namespace spic::internal::input
{
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
        */
        void SetButtons(std::vector<std::shared_ptr<spic::Button>> buttons);
    private:
        std::vector<std::shared_ptr<spic::Button>> buttons;
    };
}

#endif // BUTTONCLICKLISTENER_H_
