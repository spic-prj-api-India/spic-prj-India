#include "Transformations.hpp"
#include "Matrix.hpp"

namespace spic::internal::math 
{
	spic::Point PointToWorldSpace(const spic::Point& point,
		const spic::Point& agentHeading,
		const spic::Point& agentSide,
		const spic::Point& agentPosition)
	{
		spic::Point transPoint = point;

		S2DMatrix matTransform;

		matTransform.Rotate(agentHeading, agentSide);

		matTransform.Translate(agentPosition.x, agentPosition.y);

		matTransform.TransformPoints(transPoint);

		return transPoint;
	}

	spic::Point VectorToWorldSpace(const spic::Point& vec,
		const spic::Point& agentHeading,
		const spic::Point& agentSide)
	{
		//make a copy of the point
		spic::Point transVec = vec;

		//create a transformation matrix
		S2DMatrix matTransform;

		//rotate
		matTransform.Rotate(agentHeading, agentSide);

		//now transform the vertices
		matTransform.TransformPoints(transVec);

		return transVec;
	}

	spic::Point PointToLocalSpace(const Point& point,
		const spic::Point& agentHeading,
		const spic::Point& agentSide,
		spic::Point agentPosition)
	{
		//make a copy of the point
		Point transPoint = point;

		//create a transformation matrix
		S2DMatrix matTransform;

		float Tx = -agentPosition.Dot(agentHeading);
		float Ty = -agentPosition.Dot(agentSide);

		//create the transformation matrix
		matTransform._11(agentHeading.x); matTransform._12(agentSide.x);
		matTransform._21(agentHeading.y); matTransform._22(agentSide.y);
		matTransform._31(Tx);             matTransform._32(Ty);

		//now transform the vertices
		matTransform.TransformPoints(transPoint);

		return transPoint;
	}

	Point VectorToLocalSpace(const Point& vec,
		const Point& agentHeading,
		const Point& agentSide)
	{

		//make a copy of the point
		Point TransPoint = vec;

		//create a transformation matrix
		S2DMatrix matTransform;

		//create the transformation matrix
		matTransform._11(agentHeading.x); matTransform._12(agentSide.x);
		matTransform._21(agentHeading.y); matTransform._22(agentSide.y);

		//now transform the vertices
		matTransform.TransformPoints(TransPoint);

		return TransPoint;
	}

	void RotateAroundOrigin(spic::Point& origin, const float angle)
	{
		S2DMatrix mat;

		mat.Rotate(angle);

		mat.TransformPoints(origin);
	}
}