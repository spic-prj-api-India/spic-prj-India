#ifndef TRANSFORM_H_
#define TRANSFORM_H_

#include "Point.hpp"
#include <string>
#include <sstream> 

namespace spic {
    /**
     * @brief Instances of this class represent specific 2D transformations.
     * @spicapi
     */
    struct Transform {
        Point position; // Translation (shift)
        float rotation; // Rotation, in radians
        float scale; // Multiplication factor

        /**
         * @brief Serialize Transform into a string so it can be send trough the network
         * @return 
        */
        std::stringstream Serialize() const;

        /**
         * @brief Desserialeze an string into a current transform object
         * @param in 
        */
        void Deserialize(const std::string& in);
    };
}

#endif // TRANSFORM_H_
