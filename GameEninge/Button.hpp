#ifndef BUTTON_H_
#define BUTTON_H_

#include "UIObject.hpp"
#include "Color.hpp"
#include <functional>

namespace spic {

    /**
     * @brief Instances of this class are clickable user interface items.
     */
    class Button : public UIObject {
        public:
            typedef std::function<void()> ClickCallback;

            /**
             * @brief Default constructor
            */
            Button();

            /**
             * @brief The button's constructor
             * @param width Width of UIObject.
             * @param height Height of UIObject.
             * @param text Text inside button, if empty no Text UIbject is created.
             * @param color Color of button
             * @param texturePath Path to texture, if empty default texture will be used.
             * @sharedapi
             */
            Button(const float width, const float height, const std::string& text = "", Color color = Color::white(), const std::string& texturePath = "");
            
            /**
             * @brief This function is called when the button is clicked, which
             *        will trigger a call to the registered onClick member.
             * @spicapi
             */
            void Click();

            /**
             * @brief Register the onClick handler to be used when the button is clicked.
             * @param callback The function to register, usually a lambda. But this can be any kind of callable.
		     *			Format: [](){}
             * @spicapi
             */
            void OnClick(ClickCallback callback);

        private:
            /**
             * @brief When false, the button will not react to clicks.
             * @spicapi
             */
            bool interactable;

            /**
             * @brief The registered click handler. Format: [](){}
             * @spicapi
             */
            ClickCallback onClick;
    };
}
#endif // BUTTON_H_