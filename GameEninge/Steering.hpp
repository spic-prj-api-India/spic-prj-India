#ifndef STEERING_H_
#define STEERING_H_

#include "Component.hpp"
#include "ForceDriven.hpp"

namespace spic 
{
	enum class TargetBehaviour {
		SEEK,
		FLEE,
		ARRIVAL
	};

	/**
	 * @brief Deceleration of force driven entity, is used for arrival behaviour.
	 */
	enum class Deceleration { SLOW = 3, NORMAL = 2, FAST = 1 };

	/**
	 * @brief Calculates all steering forces
	*/
	class Steering : public Component {
	public:
		Steering(ForceDriven* agent);

		/**
		* @brief Sets obstacles
		* @param obstacles Obstacles are used for Obstacle avoidance.
		*/
		void SetObstacles(std::vector<std::shared_ptr<spic::GameObject>> obstacles);

		/**
		* @brief Sets Deceleration for Arrival steering behaviour.
		* @param deceleration Deceleration that is used when force driven entity arrives at target.
		*/
		void SetDeceleration(Deceleration deceleration = Deceleration::NORMAL);

		/**
		 * @brief Adds target with targetWeight for specific SteeringBehaviour.
		 * @param targetBehaviour SteeringBehaviour that is used for target.
		 * @param target Desired target.
		 * @param targetWeight Weight that shows how much target steering behaviour influences the steering force.
		*/
		void AddTarget(TargetBehaviour targetBehaviour, Point& target, const float targetWeight);

		/**
		 * @brief Removes target for specific SteeringBehaviour.
		 * @param targetBehaviour SteeringBehaviour that is used for target.
		 * @param target Desired target to remove.
		*/
		void RemoveTarget(TargetBehaviour targetBehaviour, Point& target);

		/**
		 * @brief Removes steering behaviour and all underlying targets.
		 * @param targetBehaviour TargetBehaviour to remove.
		*/
		void RemoveTargetBehaviour(TargetBehaviour targetBehaviour);

		/**
		 * @brief Activates wander behaviour for force driven entity.
		 * @param wanderRadius The radius of the constraining circle for the wander behaviour.
		 * @param wanderDistance The distance the wander circle is projected in front of the agent.
		 * @param wanderJitter The maximum amount of displacement along the circle each frame.
		*/
		void WanderOn(const float wanderWeight, const float wanderRadius = 1.0f, const float wanderDistance = 6.0f, const float wanderJitter = 60.0f);

		/**
		* @brief Activates wall avoidance for force driven entity.
		* @param wallAvoidanceWeight The weight of the behaviour.
		* @param wallDetectionFeelerLength The length of the 3 feelers that are attached to the front of the force driven entity.
		* @param bounds The bounds were the force driven entity needs to be kept in.
		*/
		void WallAvoidanceOn(const float wallAvoidanceWeight, const float wallDetectionFeelerLength, const Bounds& bounds);

		/**
		 * @brief Activates obstacle avoidance for force driven entity.
		 * @param obstacleAvoidanceWeight The weight of the behaviour.
		 * @param boxLength The length of the box that is attached to the force driven entity.
		*/
		void ObstacleAvoidanceOn(const float obstacleAvoidanceWeight, const  float boxLength);

		/**
		* @brief Calculates steering force.
		* @param addSteeringForceCallback Callback that adds forces to steering force.
		*/
		void Calculate(std::function<bool(Point force)> addSteeringForceCallback);
	private:
		/**
		 * @brief Add all target forces to steering force.
		 * @param addSteeringForceCallback Callback that adds forces to steering force.
		*/
		void AddTargetForces(std::function<bool(Point force)> addSteeringForceCallback);

		/**
		 * @brief Seek to target and return steering force.
		 * @return spic::Point Steering force.
		*/
		Point Seek(Point target);

		/**
		* @brief Flee from target and return steering force.
		* @return spic::Point Steering force.
		*/
		Point Flee(Point target);

		/**
		* @brief Arrive at target and return steering force.
		* @return spic::Point Steering force.
		*/
		Point Arrival(Point target);

		/**
		* @brief Wander randomly around scene and return steering force.
		* @return spic::Point Steering force.
		*/
		Point Wander();

		/**
		* @brief Calculates steering force to avoid walls.
		* @return spic::Point Steering force.
		*/
		Point WallAvoidance();

		/**
		* @brief Calculates steering force to avoid obstacles.
		* @return spic::Point Steering force.
		*/
		Point ObstacleAvoidance();
	private:
		/**
		* @brief agent used for steering
		*/
		const ForceDriven* agent;

		/**
		* @brief Target properties.
		*       Every steering force has a map with a target as a key and a target weight as value.
		*/
		std::map<spic::TargetBehaviour, std::map<std::reference_wrapper<Point>, float, std::less<Point>>> steeringBehavioursIncludingTargets;

		/**
		* @brief Wall avoidance properties.
		*/
		bool useWallAvoidance;
		float wallAvoidanceWeight;
		float wallDetectionFeelerLength;
		Bounds bounds;

		/**
		* @brief Obstacle avoidance properties.
				When feeler reaches certain treshold start aplying obstacle avoidance force
		*/
		bool useObstacleAvoidance;
		float obstacleAvoidanceWeight;
		std::vector<std::shared_ptr<spic::GameObject>> obstacles;
		float boxLength;

		/**
		* @brief Wander properties.
		*/
		bool useWander;
		float wanderWeight;
		float wanderRadius;
		float wanderDistance;
		float wanderJitter;

		/**
		* @brief Arrival properties.
		*/
		Deceleration deceleration;
	};
}

#endif // STEERING_H_