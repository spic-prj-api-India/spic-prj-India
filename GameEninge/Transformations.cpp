#include "Transformations.hpp"
#include "Matrix.hpp"

namespace spic::internal::math {
	spic::Point PointToWorldSpace(const spic::Point& point,
		const spic::Point& AgentHeading,
		const spic::Point& AgentSide,
		const spic::Point& AgentPosition)
	{
		spic::Point transPoint = point;

		S2DMatrix matTransform;

		matTransform.Rotate(AgentHeading, AgentSide);

		matTransform.Translate(AgentPosition.x, AgentPosition.y);

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