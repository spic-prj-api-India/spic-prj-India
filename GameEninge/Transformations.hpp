#ifndef TRANSFORMATIONS_H_
#define TRANSFORMATIONS_H_

#include "Point.hpp"

namespace spic::internal::math {
	/**
	 * @brief Transforms a point from the agent's local space into world space.
	 * @param point Point of transformation.
	 * @param agentHeading Direction agent is heading to.
	 * @param agentSide Side of agent.
	 * @param agentPosition Position of agent.
	*/
	spic::Point PointToWorldSpace(const spic::Point& point,
		const spic::Point& agentHeading,
		const spic::Point& agentSide,
		const spic::Point& agentPosition);

	/**
	 * @brief Transforms a vector from the agent's local space into world space.
	 * @param vec Vector to be transformed.
	 * @param agentHeading Direction agent is heading to.
	 * @param agentSide Side of agent.
	*/
	spic::Point VectorToWorldSpace(const spic::Point& vec,
		const spic::Point& agentHeading,
		const spic::Point& agentSide);

	/**
	 * @brief Transforms a point from the agent's to local space.
	 * @param point Point of transformation.
	 * @param agentHeading Direction agent is heading to.
	 * @param agentSide Side of agent.
	 * @param agentPosition Position of agent.
	*/
	spic::Point PointToLocalSpace(const Point& point,
		const spic::Point& agentHeading,
		const spic::Point& agentSide,
		spic::Point agentPosition);

	/**
	 * @brief Transforms a vector to local space.
	 * @param vec Vector to be converted.
	 * @param agentHeading Direction agent is heading to.
	 * @param agentSide Side of agent.
	*/
	spic::Point VectorToLocalSpace(const spic::Point& vec,
		const spic::Point& agentHeading,
		const spic::Point& agentSide);

	/**
	 * @brief Rotates a vector ang rads around the origin.
	 * @param origin Point that is rotated around.
	 * @param angle Angle in rad.
	*/
	void RotateAroundOrigin(spic::Point& origin, const float angle);
}

#endif // TRANSFORMATIONS_H_