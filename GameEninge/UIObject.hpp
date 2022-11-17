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
    };

}

#endif // UIOBJECT_H_
