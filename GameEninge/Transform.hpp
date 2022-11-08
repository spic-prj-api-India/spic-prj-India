#ifndef TRANSFORM_H_
#define TRANSFORM_H_

#include "Point.hpp"

namespace spic {
    /**
     * @brief Instances of this class represent specific 2D transformations.
     * @spicapi
     */
    struct Transform {
        Point position; // Translation (shift)
        float rotation; // Rotation, in radians
        float scale; // Multiplication factor
    };
}

#endif // TRANSFORM_H_
