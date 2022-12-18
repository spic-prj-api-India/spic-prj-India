#include "Transformations.hpp"
#include "Matrix.hpp"

namespace spic::internal::math {
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

	void RotateAroundOrigin(spic::Point& origin, const float angle)
	{
		S2DMatrix mat;

		mat.Rotate(angle);

		mat.TransformPoints(origin);
	}
}