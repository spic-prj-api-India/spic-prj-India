#ifndef TRANSFORMATIONS_H_
#define TRANSFORMATIONS_H_

#include "Point.hpp"

namespace spic::internal::math {
	spic::Point PointToWorldSpace(const spic::Point& point,
		const spic::Point& AgentHeading,
		const spic::Point& AgentSide,
		const spic::Point& AgentPosition);

	void RotateAroundOrigin(spic::Point& origin, const float angle);
}

#endif // TRANSFORMATIONS_H_