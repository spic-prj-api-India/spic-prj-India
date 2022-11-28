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
            float Width() const { return width; }
            float Height() const { return height; }

            void Width(const float widt) { width = widt; }
            void Height(const float height) { this->height = height; }
    };

}

#endif // UIOBJECT_H_
