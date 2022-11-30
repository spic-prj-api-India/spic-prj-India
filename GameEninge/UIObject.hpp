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
            virtual ~UIObject() = default;

            float Width() const;
            float Height() const;

            void Width(const float newWidth);
            void Height(const float newHeight);
    };

}

#endif // UIOBJECT_H_
