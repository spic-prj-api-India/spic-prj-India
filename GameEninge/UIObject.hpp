#ifndef UIOBJECT_H_
#define UIOBJECT_H_

#include "GameObject.hpp"

namespace spic {
    /**
     * @brief Base class for a user interface object like Button or Text.
     * @spicapi
     */
    class UIObject : public GameObject {
        private:
            float width;
            float height;

        public:
            UIObject();
            UIObject(const float newWidth, const float newHeight);

            /**
             * @brief Gets width of UIObject.
             * @return float.
             * @spicapi
            */
            float Width() const;

            /**
             * @brief Gets height of UIObject.
             * @return float.
             * @spicapi
            */
            float Height() const;

            /**
            * @brief Sets width of UIObject.
            * @param newWidth Desired value.
            * @spicapi
            */
            void Width(const float newWidth);

            /**
            * @brief Sets height of UIObject.
            * @param newHeight Desired value.
            * @spicapi
            */
            void Height(const float newHeight);
    };
}

#endif // UIOBJECT_H_
