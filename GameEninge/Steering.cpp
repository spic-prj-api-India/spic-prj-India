#include "Steering.hpp"
#include "Random.hpp"
#include "GeneralHelper.hpp"
#include "Defaults.hpp"
#include "Collider.hpp"
#include "Transformations.hpp"
#include "Settings.hpp"
#include "Debug.hpp"
#include "Obstacle.hpp"

namespace spic {
	using namespace internal::math;

	Steering::Steering(ForceDriven* agent) : agent{ agent }, useWallAvoidance { false },
		useObstacleAvoidance{ false }, useWander{ false }, deceleration{ spic::Deceleration::NORMAL }
	{
	}

	void Steering::SetObstacles(std::vector<std::shared_ptr<spic::GameObject>> obstacles)
	{
		this->obstacles = obstacles;
	}

	void Steering::AddTarget(TargetBehaviour targetBehaviour, Point& target, const float targetWeight)
	{
		if (this->steeringBehavioursIncludingTargets.count(targetBehaviour) == 0)
			steeringBehavioursIncludingTargets[targetBehaviour] = {};
		this->steeringBehavioursIncludingTargets[targetBehaviour][target] = targetWeight;
	}

	void Steering::RemoveTarget(TargetBehaviour targetBehaviour, Point& target)
	{
		if (this->steeringBehavioursIncludingTargets.count(targetBehaviour) == 0)
			return;
		if (this->steeringBehavioursIncludingTargets[targetBehaviour].count(target) == 0)
			return;
		this->steeringBehavioursIncludingTargets[targetBehaviour].erase(target);
	}

	void Steering::RemoveTargetBehaviour(TargetBehaviour targetBehaviour)
	{
		if (this->steeringBehavioursIncludingTargets.count(targetBehaviour) == 0)
			return;
		this->steeringBehavioursIncludingTargets.erase(targetBehaviour);
	}

	void Steering::SetDeceleration(Deceleration deceleration)
	{
		this->deceleration = deceleration;
	}

	void Steering::WanderOn(const float wanderWeight, const float wanderRadius, const float wanderDistance, const float wanderJitter)
	{
		this->useWander = true;
		this->wanderWeight = wanderWeight;
		this->wanderRadius = wanderRadius;
		this->wanderDistance = wanderDistance;
		this->wanderJitter = wanderJitter;
	}

	void Steering::WallAvoidanceOn(const float wallAvoidanceWeight, const float wallDetectionFeelerLength, const Bounds& bounds)
	{
		this->useWallAvoidance = true;
		this->wallAvoidanceWeight = wallAvoidanceWeight;
		this->wallDetectionFeelerLength = wallDetectionFeelerLength;
		this->bounds = bounds;
	}

	void Steering::ObstacleAvoidanceOn(const float obstacleAvoidanceWeight, const float boxLength)
	{
		this->useObstacleAvoidance = true;
		this->obstacleAvoidanceWeight = obstacleAvoidanceWeight;
		this->boxLength = boxLength;
	}

	void Steering::Calculate(std::function<bool(Point force)> addSteeringForceCallback)
	{
		Point force;
		if (useWallAvoidance) {
			force = WallAvoidance() * wallAvoidanceWeight;
			if (!addSteeringForceCallback(force))
				return;
		}
		if (useObstacleAvoidance) {
			force = ObstacleAvoidance() * obstacleAvoidanceWeight;
			if (!addSteeringForceCallback(force))
				return;
		}
		if (useWander) {
			force = Wander() * wanderWeight;
			if (!addSteeringForceCallback(force))
				return;
		}
		AddTargetForces(addSteeringForceCallback);
	}

	void Steering::AddTargetForces(std::function<bool(Point force)> addSteeringForceCallback)
	{
		Point force;
		for (const auto& steeringBehaviourIncludingTargets : steeringBehavioursIncludingTargets) {
			TargetBehaviour steeringBehaviour = steeringBehaviourIncludingTargets.first;
			const auto& targets = steeringBehaviourIncludingTargets.second;
			for (const auto& targetWithWeight : targets) {
				const spic::Point& target = targetWithWeight.first;
				const float targetWeight = targetWithWeight.second;

				switch (steeringBehaviour) {
				case TargetBehaviour::ARRIVAL:
					force = Arrival(target) * targetWeight;
					break;
				case TargetBehaviour::FLEE:
					force = Flee(target) * targetWeight;
					break;
				case TargetBehaviour::SEEK:
					force = Seek(target) * targetWeight;
					break;
				default: continue;
				}
			}
			if (!addSteeringForceCallback(force))
				return;
		}
	}

	Point Steering::Seek(Point target)
	{
		const Point& location = this->agent->Transform()->position;

		Point desiredVelocity = target - location;

		if (desiredVelocity.Length() == 0.0f)
			return {};

		desiredVelocity.Normalize();
		desiredVelocity *= this->agent->MaxSpeed();

		return (desiredVelocity - this->agent->Velocity());
	}

	Point Steering::Flee(Point target)
	{
		Point& location = this->agent->Transform()->position;

		Point desiredVelocity = location - target;

		if (desiredVelocity.Length() == 0.0f)
			return {};

		desiredVelocity.Normalize();
		desiredVelocity *= this->agent->MaxSpeed();

		return (desiredVelocity - this->agent->Velocity());
	}

	Point Steering::Arrival(Point target)
	{
		Point& location = this->agent->Transform()->position;

		Point desiredVelocity = target - location;
		const float distance = desiredVelocity.Length();

		if (distance <= 5.f)
			return {};

		const float decelerationTweaker = 0.3f;

		float speed = distance / ((float)deceleration * decelerationTweaker);

		speed = std::min(speed, this->agent->MaxSpeed());

		desiredVelocity *= speed;
		// Can't be zero, because of distance check
		desiredVelocity /= distance;

		return (desiredVelocity - this->agent->Velocity());
	}

	Point Steering::Wander()
	{
		Point target;
		const Point& location = this->agent->Transform()->position;
		const Point& heading = this->agent->Heading();
		const Point& side = this->agent->Side();

		target += Point(ClampedRandomFloat() * wanderJitter,
			ClampedRandomFloat() * wanderJitter);

		target.Normalize();

		target *= wanderRadius;

		const Point targetLocal = target + Point(wanderDistance, 0.0f);

		Point targetWorld = PointToWorldSpace(targetLocal,
			heading,
			side,
			location);

		Point desiredVelocity = targetWorld - location;
		desiredVelocity.Normalize();
		desiredVelocity *= this->agent->MaxSpeed();

		return (desiredVelocity - this->agent->Velocity());
	}

	Point Steering::WallAvoidance()
	{
		Point location = this->agent->Transform()->position;
		const Point& heading = this->agent->Heading();
		Point halfSize = this->agent->GetComponent<Collider>()->Size() / 2;
		Point center = { location.x + halfSize.x,location.y + halfSize.y };
		Point top = center + (heading * halfSize.y);
		std::vector<Point> feelers(3);

		feelers[0] = top + (heading * wallDetectionFeelerLength);

		Point temp = heading;
		RotateAroundOrigin(temp, spic::internal::defaults::HALF_PI * 3.5f);
		feelers[1] = top + (temp * wallDetectionFeelerLength);

		temp = heading;
		RotateAroundOrigin(temp, spic::internal::defaults::HALF_PI * 0.5f);
		feelers[2] = top + (temp * wallDetectionFeelerLength);

		if (settings::WALL_AVOIDANCE_FEELERS_VISIBILITY) {
			debug::DrawLine(top, feelers[0]);
			debug::DrawLine(top, feelers[1]);
			debug::DrawLine(top, feelers[2]);
		}

		float distToThisIP = 0.0;
		float distToClosestIP = std::numeric_limits<float>::max();

		Point walls[5] = { Point(bounds.Left(), bounds.Top()),
			Point(bounds.Left(), bounds.Top() + bounds.Height()),
			Point(bounds.Left() + bounds.Width(), bounds.Top() + bounds.Height()),
			Point(bounds.Left() + bounds.Width(), bounds.Top()),
			Point(bounds.Left(), bounds.Top())
		};
		debug::DrawLine(walls[0], walls[1]);
		debug::DrawLine(walls[1], walls[2]);
		debug::DrawLine(walls[2], walls[3]);
		debug::DrawLine(walls[3], walls[4]);

		int closestWallIndex = -1;

		Point steeringForce, point, closestPoint;

		for (auto& feeler : feelers) {
			for (int wallIndex = 0; wallIndex < 4; wallIndex++) {
				if (spic::general_helper::LineIntersection(top,
					feeler,
					walls[wallIndex],
					walls[wallIndex + 1],
					point,
					distToThisIP))
				{
					if (distToThisIP < distToClosestIP)
					{
						distToClosestIP = distToThisIP;

						closestWallIndex = wallIndex;

						closestPoint = point;
					}
				}
			}

			if (closestWallIndex != -1)
			{
				const Point overShoot = feeler - closestPoint;

				Point temp = (walls[closestWallIndex] - walls[closestWallIndex + 1]);
				temp.Normalize();
				Point normal(-temp.y, temp.x);

				steeringForce = normal * overShoot.Length();
			}
		}
		return steeringForce;
	}

	Point Steering::ObstacleAvoidance()
	{
		Point location = this->agent->Transform()->position;
		const Point& heading = this->agent->Heading();
		const Point& side = this->agent->Side();
		float realBoxLength = boxLength;

		std::shared_ptr<GameObject> closestIntersectingObstacle = nullptr;

		//this will be used to track the distance to the CIB
		float distToClosestIP = MaxFloat;

		//this will record the transformed local coordinates of the CIB
		Point localPosOfClosestObstacle;

		for (const auto& obstacle : obstacles)
		{
			Point obstacleLocation = obstacle->Transform()->position;
			float obstacleRadius = spic::TypeHelper::CastSharedPtrToType<Obstacle>(obstacle)->BRadius();
			const Point to = obstacleLocation - location;

			const float range = realBoxLength + obstacleRadius;

			//if entity within range, tag for further consideration. (working in
			//distance-squared space to avoid sqrts)
			if ((to.LengthSq() < range * range))
			{

				//calculate this obstacle's position in local space
				Point localPos = PointToLocalSpace(obstacleLocation,
					heading,
					side,
					location);

				//if the local position has a negative x value then it must lay
				//behind the agent. (in which case it can be ignored)
				if (localPos.x >= 0)
				{
					//if the distance from the x axis to the object's position is less
					//than its radius + half the width of the detection box then there
					//is a potential intersection.
					const float expandedRadius = obstacleRadius + this->agent->BRadius();

					/*if (fabs(LocalPos.y) < ExpandedRadius)
					{*/
					//now to do a line/circle intersection test. The center of the 
					//circle is represented by (cX, cY). The intersection points are 
					//given by the formula x = cX +/-sqrt(r^2-cY^2) for y=0. 
					//We only need to look at the smallest positive value of x because
					//that will be the closest point of intersection.
					const float cX = localPos.x;
					const float cY = localPos.y;

					//we only need to calculate the sqrt part of the above equation once
					const float sqrtPart = sqrt(expandedRadius * expandedRadius - cY * cY);

					float ip = cX - sqrtPart;

					if (ip <= 0.0)
					{
						ip = cX + sqrtPart;
					}

					//test to see if this is the closest so far. If it is keep a
					//record of the obstacle and its local coordinates
					if (ip < distToClosestIP)
					{
						distToClosestIP = ip;

						closestIntersectingObstacle = obstacle;
						//debug::DrawLine(localPos, obstacleLocation, Color::red());
						localPosOfClosestObstacle = localPos;
					}
				}
			}
		}

		//if we have found an intersecting obstacle, calculate a steering 
		//force away from it
		Point steeringForce;

		if (closestIntersectingObstacle != nullptr)
		{
			//the closer the agent is to an object, the stronger the 
			//steering force should be
			const float multiplier = 1.0f + (boxLength - localPosOfClosestObstacle.x) /
				boxLength;

			//calculate the lateral force
			float obstacleRadius = closestIntersectingObstacle->GetComponent<Collider>()->Size().x / 2;
			steeringForce.y = (obstacleRadius -
				localPosOfClosestObstacle.y) * multiplier;

			//apply a braking force proportional to the obstacles distance from
			//the MovingEntity. 
			const float brakingWeight = 0.2f;

			steeringForce.x = (obstacleRadius -
				localPosOfClosestObstacle.x) *
				brakingWeight;
		}

		//finally, convert the steering vector from local to world space
		return VectorToWorldSpace(steeringForce,
			heading,
			side);
	}
}