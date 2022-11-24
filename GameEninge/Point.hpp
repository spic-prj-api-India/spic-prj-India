#ifndef POINT_H_
#define POINT_H_

namespace spic {

    /**
     * @brief Struct representing both a 2D point and a 2D vector.
     * @spicapi
     */
    struct Point {
        float x;
        float y;

        /// @brief Dotproduct
        /// @param point 
        /// @return 
        float operator *(const Point& point);
    };

}

#endif // POINT_H_
