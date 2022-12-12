#include "Matrix.hpp"
#include <cfloat>
#include <corecrt_math.h>

using namespace spic::internal::math;

S2DMatrix::S2DMatrix()
{
	Identity();
}

void S2DMatrix::Identity()
{
	matrix._11 = 1.0f; matrix._12 = 0.0f; matrix._13 = 0.0f;
	matrix._21 = 0.0f; matrix._22 = 1.0f; matrix._23 = 0.0f;
	matrix._31 = 0.0f; matrix._32 = 0.0f; matrix._33 = 1.0f;
}

void S2DMatrix::Translate(float x, float y)
{
	Matrix mat;

	mat._11 = 1.0f; mat._12 = 0.0f; mat._13 = 0.0f;
	mat._21 = 0.0f; mat._22 = 1.0f; mat._23 = 0.0f;
	mat._31 = x;    mat._32 = y;    mat._33 = 1.0f;

	MatrixMultiply(mat);
}

void S2DMatrix::Rotate(float rotation)
{
	Matrix mat;

	const float sin = sinf(rotation);
	const float cos = cosf(rotation);

	mat._11 = cos;  mat._12 = sin;  mat._13 = 0.0f;
	mat._21 = -sin; mat._22 = cos;  mat._23 = 0.0f;
	mat._31 = 0.0f; mat._32 = 0.0f; mat._33 = 1.0f;

	MatrixMultiply(mat);
}

void S2DMatrix::Rotate(const spic::Point& heading, const spic::Point& side)
{
	Matrix mat;

	mat._11 = heading.x; mat._12 = heading.y; mat._13 = 0.0f;
	mat._21 = side.x;    mat._22 = side.y;    mat._23 = 0.0f;
	mat._31 = 0.0f;      mat._32 = 0.0f;      mat._33 = 1.0f;

	MatrixMultiply(mat);
}

void S2DMatrix::TransformPoints(spic::Point& point)
{
	const float tempX = (matrix._11 * point.x) + (matrix._21 * point.y) + (matrix._31);
	const float tempY = (matrix._12 * point.x) + (matrix._22 * point.y) + (matrix._32);

	point.x = tempX;
	point.y = tempY;
}

S2DMatrix::Matrix::Matrix()
{
	_11 = 0.0f; _12 = 0.0f; _13 = 0.0f;
	_21 = 0.0f; _22 = 0.0f; _23 = 0.0f;
	_31 = 0.0f; _32 = 0.0f; _33 = 0.0f;
}

void S2DMatrix::MatrixMultiply(Matrix& mIn)
{
	Matrix mat_temp;

	//first row
	mat_temp._11 = (matrix._11 * mIn._11) + (matrix._12 * mIn._21) + (matrix._13 * mIn._31);
	mat_temp._12 = (matrix._11 * mIn._12) + (matrix._12 * mIn._22) + (matrix._13 * mIn._32);
	mat_temp._13 = (matrix._11 * mIn._13) + (matrix._12 * mIn._23) + (matrix._13 * mIn._33);

	//second
	mat_temp._21 = (matrix._21 * mIn._11) + (matrix._22 * mIn._21) + (matrix._23 * mIn._31);
	mat_temp._22 = (matrix._21 * mIn._12) + (matrix._22 * mIn._22) + (matrix._23 * mIn._32);
	mat_temp._23 = (matrix._21 * mIn._13) + (matrix._22 * mIn._23) + (matrix._23 * mIn._33);

	//third
	mat_temp._31 = (matrix._31 * mIn._11) + (matrix._32 * mIn._21) + (matrix._33 * mIn._31);
	mat_temp._32 = (matrix._31 * mIn._12) + (matrix._32 * mIn._22) + (matrix._33 * mIn._32);
	mat_temp._33 = (matrix._31 * mIn._13) + (matrix._32 * mIn._23) + (matrix._33 * mIn._33);

	matrix = mat_temp;
}