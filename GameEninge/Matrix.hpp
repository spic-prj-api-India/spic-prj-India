#ifndef MATRIX_H_
#define MATRIX_H_

#include "Point.hpp"

/**
 * @brief Contains math related classes and function(s)
*/
namespace spic::internal::math 
{
    /**
     * @brief Matrix that can be used to translate and rotate matrixes.
    */
    class S2DMatrix {
    public:
        /**
         * @brief Initializes the matrix to an identity matrix.
        */
        S2DMatrix();

        /**
         * @brief Creates an identity matrix.
        */
        void Identity();

        /**
         * @brief Creates a transformation matrix.
         * @param x X of transformation.
         * @param y Y of transformation.
        */
        void Translate(const float x, const float y);

        /**
         * @brief Creates a rotation matrix.
         * @param rotation Rotation in grad.
        */
        void Rotate(const float rotation);

        /**
         * @brief Creates a rotation matrix.
         * @param heading Direction of 2D Vector.
         * @param side Side of 2D Vector.
        */
        void Rotate(const spic::Point& heading, const spic::Point& side);

        /**
         * @brief Applies a transformation matrix to a point.
         * @param point Point that transformation is applied on.
        */
        void TransformPoints(spic::Point& point);

        void _11(float val) { matrix._11 = val; }
        void _12(float val) { matrix._12 = val; }
        void _13(float val) { matrix._13 = val; }

        void _21(float val) { matrix._21 = val; }
        void _22(float val) { matrix._22 = val; }
        void _23(float val) { matrix._23 = val; }

        void _31(float val) { matrix._31 = val; }
        void _32(float val) { matrix._32 = val; }
        void _33(float val) { matrix._33 = val; }
    private:
        struct Matrix
        {
            float _11, _12, _13;
            float _21, _22, _23;
            float _31, _32, _33;

            Matrix();
        };

        /**
         * @brief Multiplies matrix with mIn.
         * @param mIn Matrix that will be multiplied.
        */
        void MatrixMultiply(const Matrix& mIn);
    private:
        Matrix matrix;
    };
}

#endif // MATRIX_H_