#ifndef MATRIX_H_
#define MATRIX_H_

#include "Point.hpp"

namespace spic::internal::math {
    class S2DMatrix {
    public:
        S2DMatrix();

        void Identity();
        void Translate(float x, float y);
        void Rotate(float rotation);
        void Rotate(const spic::Point& heading, const spic::Point& side);
        void TransformPoints(spic::Point& point);
    private:
        struct Matrix
        {
            float _11, _12, _13;
            float _21, _22, _23;
            float _31, _32, _33;

            Matrix();
        };

        void MatrixMultiply(Matrix& mIn);
    private:
        Matrix matrix;
    };
}

#endif // MATRIX_H_