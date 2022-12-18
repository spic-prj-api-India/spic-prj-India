#include "ForceDriven.hpp"
#include "RigidBody.hpp"
#include "GeneralHelper.hpp"
#include "Defaults.hpp"
#include "Transformations.hpp"
#include "Random.hpp"
#include <functional>
#include "Debug.hpp"
#include "Collider.hpp"

using namespace spic::internal::math;

namespace spic {
	ForceDriven::ForceDriven(SumMethod sumMethod, const float maxSteeringForce, const float maxSpeed, const float angleSensitivity) : GameObject(),
		sumMethod{ sumMethod }, maxSteeringForce{ maxSteeringForce }, maxSpeed{ maxSpeed },
		angleSensitivity{ angleSensitivity }, paused{ true }, useWallAvoidance{ false },
		useObstacleAvoidance{ false }, useSeperation{ false }, useAlignment{ false },
		useCohesion{ false }, useWander{ false }, deceleration{ spic::Deceleration::NORMAL }
	{
		this->steeringBehavioursIncludingTargets;
	}

	Point ForceDriven::Velocity() const
	{
		std::shared_ptr<RigidBody> body = this->GetComponent<RigidBody>();
		return body->Velocity();
	}

	Point ForceDriven::Heading() const
	{
		return heading;
	}

	float ForceDriven::Mass() const
	{
		std::shared_ptr<RigidBody> body = this->GetComponent<RigidBody>();
		return body->Mass();
	}

	void ForceDriven::SetObstacles(std::vector<std::shared_ptr<spic::GameObject>> obstacles)
	{
		obstacles = std::move(obstacles);
	}

	void ForceDriven::AddTarget(TargetBehaviour targetBehaviour, Point& target, const float targetWeight)
	{
		if (this->steeringBehavioursIncludingTargets.count(targetBehaviour) == 0)
			steeringBehavioursIncludingTargets[targetBehaviour] = {};
		this->steeringBehavioursIncludingTargets[targetBehaviour][target] = targetWeight;
	}

	void ForceDriven::RemoveTarget(TargetBehaviour targetBehaviour, Point& target)
	{
		if (this->steeringBehavioursIncludingTargets.count(targetBehaviour) == 0)
			return;
		if (this->steeringBehavioursIncludingTargets[targetBehaviour].count(target) == 0)
			return;
		this->steeringBehavioursIncludingTargets[targetBehaviour].erase(target);
	}

	void ForceDriven::RemoveTargetBehaviour(TargetBehaviour targetBehaviour)
	{
		if (this->steeringBehavioursIncludingTargets.count(targetBehaviour) == 0)
			return;
		this->steeringBehavioursIncludingTargets.erase(targetBehaviour);
	}

	void ForceDriven::SetDeceleration(Deceleration deceleration)
	{
		this->deceleration = deceleration;
	}

	void ForceDriven::Wander(const float wanderWeight, const float wanderRadius, const float wanderDistance, const float wanderJitter)
	{
		this->useWander = true;
		this->wanderWeight = wanderWeight;
		this->wanderRadius = wanderRadius;
		this->wanderDistance = wanderDistance;
		this->wanderJitter = wanderJitter;
	}

	void ForceDriven::WallAvoidance(const float wallAvoidanceWeight, const float wallDetectionFeelerLength, const Bounds& bounds)
	{
		this->useWallAvoidance = true;
		this->wallAvoidanceWeight = wallAvoidanceWeight;
		this->wallDetectionFeelerLength = wallDetectionFeelerLength;
		this->bounds = bounds;
	}

	void ForceDriven::ObstacleAvoidance(const float obstacleAvoidanceWeight, const float boxLength)
	{
		this->useObstacleAvoidance = true;
		this->obstacleAvoidanceWeight = obstacleAvoidanceWeight;
		this->boxLength = boxLength;
	}

	void ForceDriven::Seperation(const float seperationWeight, const float desiredSeparation)
	{
		this->useSeperation = true;
		this->seperationWeight = seperationWeight;
		this->desiredSeparation = desiredSeparation;
	}

	void ForceDriven::Alignment(const float alignmentWeight, const float viewRadius)
	{
		this->useAlignment = true;
		this->alignmentWeight = alignmentWeight;
		this->viewRadius = viewRadius;
	}

	void ForceDriven::Cohesion(const float cohesionWeight, const float viewRadius)
	{
		this->useCohesion = true;
		this->cohesionWeight = cohesionWeight;
		this->viewRadius = viewRadius;
	}

	void ForceDriven::StartForceDrivenEntity()
	{
		paused = false;
	}

	void ForceDriven::UpdateForceDrivenEntity(const std::vector<std::shared_ptr<ForceDriven>>& forceDrivenEntities)
	{
		if (paused)
			return;
		if (useSeperation || useAlignment || useCohesion)
		{
			TagNeighbors(forceDrivenEntities);
		}
		Point steeringForce = Calculate();
		ApplyForce(steeringForce);
	}

	void ForceDriven::StopForceDrivenEntity()
	{
		paused = true;
	}

	void ForceDriven::TagNeighbors(const std::vector<std::shared_ptr<ForceDriven>>& forceDrivenEntities)
	{
		neighbors = {};
		for (const auto& forceDrivenEntity : forceDrivenEntities) {
			if (forceDrivenEntity.get() == this)
				continue;
			Point toAgent = Transform()->position - forceDrivenEntity->Transform()->position;
			const float distance = toAgent.Length();

			if (distance > 0.0f && distance < viewRadius) {
				neighbors.emplace_back(forceDrivenEntity);
			}
		}
	}

	Point ForceDriven::Calculate()
	{
		switch (sumMethod) {
		case SumMethod::WEIGHTED_AVERAGE:
			return CalculateWeightedSum();
		case SumMethod::PRIORITIZED:
			return CalculatePrioritized();
		default:
			return {};
		}
	}

	Point ForceDriven::CalculateWeightedSum()
	{
		Point steeringForce{};

		Point force;
		if (useWallAvoidance)
		{
			force = WallAvoidance() * wallAvoidanceWeight;
			steeringForce += force;
		}
		if (useObstacleAvoidance)
		{
			force = ObstacleAvoidance() * obstacleAvoidanceWeight;
			steeringForce += force;
		}
		if (useWander)
		{
			force = Wander() * wanderWeight;
			steeringForce += force;
		}
		AddSteeringForces([this, &steeringForce](Point force) {
			steeringForce += force;
			return false;
			});
		if (useSeperation)
		{
			force = Seperate() * seperationWeight;
			steeringForce += force;
		}
		if (useAlignment)
		{
			force = Align() * alignmentWeight;
			steeringForce += force;
		}
		if (useCohesion)
		{
			force = Cohere() * cohesionWeight;
			steeringForce += force;
		}
		if (steeringForce.Length() > maxSteeringForce) {
			steeringForce.Normalize();
			steeringForce *= maxSteeringForce;
		}
		return steeringForce;
	}

	Point ForceDriven::CalculatePrioritized()
	{
		Point steeringForce{};

		Point force;
		if (useWallAvoidance)
		{
			force = WallAvoidance() * wallAvoidanceWeight;
			if (!steeringForce.Accumulate(force, maxSteeringForce)) return steeringForce;
		}
		if (useObstacleAvoidance)
		{
			force = ObstacleAvoidance() * obstacleAvoidanceWeight;
			if (!steeringForce.Accumulate(force, maxSteeringForce)) return steeringForce;
		}
		if (useWander)
		{
			force = Wander() * wanderWeight;
			if (!steeringForce.Accumulate(force, maxSteeringForce)) return steeringForce;
		}
		AddSteeringForces([this, &steeringForce](Point force) {
			if (!steeringForce.Accumulate(force, maxSteeringForce)) return true;
			return false;
			});
		if (useSeperation)
		{
			force = Seperate() * seperationWeight;
			if (!steeringForce.Accumulate(force, maxSteeringForce)) return steeringForce;
		}
		if (useAlignment)
		{
			force = Align() * alignmentWeight;
			if (!steeringForce.Accumulate(force, maxSteeringForce)) return steeringForce;
		}
		if (useCohesion)
		{
			force = Cohere() * cohesionWeight;
			if (!steeringForce.Accumulate(force, maxSteeringForce)) return steeringForce;
		}
		return steeringForce;
	}

	void ForceDriven::AddSteeringForces(std::function<bool(Point force)> addSteeringForceCallback)
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
			if (addSteeringForceCallback(force))
				return;
		}
	}

	Point ForceDriven::Seek(Point target)
	{
		const Point& location = this->Transform()->position;

		Point desiredVelocity = target - location;

		if (desiredVelocity.Length() == 0.0f)
			return {};

		desiredVelocity.Normalize();
		desiredVelocity *= maxSpeed;

		return (desiredVelocity - Velocity());
	}

	Point ForceDriven::Flee(Point target)
	{
		Point& location = this->Transform()->position;

		Point desiredVelocity = location - target;

		if (desiredVelocity.Length() == 0.0f)
			return {};

		desiredVelocity.Normalize();
		desiredVelocity *= maxSpeed;

		return (desiredVelocity - Velocity());
	}

	Point ForceDriven::Arrival(Point target)
	{
		Point& location = this->Transform()->position;

		Point desiredVelocity = target - location;
		const float distance = desiredVelocity.Length();

		if (distance <= 5.f)
			return {};

		const float decelerationTweaker = 0.3f;

		float speed = distance / ((float)deceleration * decelerationTweaker);

		speed = std::min(speed, maxSpeed);

		desiredVelocity *= speed;
		// Can't be zero, because of distance check
		desiredVelocity /= distance;

		return (desiredVelocity - Velocity());
	}

	Point ForceDriven::Wander()
	{
		Point target;
		const Point& location = this->Transform()->position;

		target += Point(ClampedRandomFloat() * wanderJitter,
			ClampedRandomFloat() * wanderJitter);

		target.Normalize();

		target *= wanderRadius;

		const Point targetLocal = target + Point(wanderDistance, 0.0f);

		Point targetWorld = PointToWorldSpace(targetLocal,
			heading,
			heading.Perp(),
			location);

		Point desiredVelocity = targetWorld - location;
		desiredVelocity.Normalize();
		desiredVelocity *= maxSpeed;

		return (desiredVelocity - Velocity());
	}

	Point ForceDriven::WallAvoidance()
	{
		Point location = this->Transform()->position;
		Point halfSize = this->GetComponent<Collider>()->Size() / 2;
		Point center = { location.x + halfSize.x,location.y + halfSize.y };
		Point top = center + (heading * halfSize.y);
		std::vector<Point> feelers(3);

		feelers[0] = top + (heading * wallDetectionFeelerLength);

		Point temp = heading;
		RotateAroundOrigin(temp, spic::internal::Defaults::HALF_PI * 3.5f);
		feelers[1] = top + (temp * wallDetectionFeelerLength);

		temp = heading;
		RotateAroundOrigin(temp, spic::internal::Defaults::HALF_PI * 0.5f);
		feelers[2] = top + (temp * wallDetectionFeelerLength);

		if (Debug::WALL_AVOIDANCE_FEELERS_VISIBILITY) {
			Debug::DrawLine(top, feelers[0]);
			Debug::DrawLine(top, feelers[1]);
			Debug::DrawLine(top, feelers[2]);
		}

		float distToThisIP = 0.0;
		float distToClosestIP = std::numeric_limits<float>::max();

		Point walls[5] = { Point(bounds.Left(), bounds.Top()),
			Point(bounds.Left(), bounds.Top() + bounds.Height()),
			Point(bounds.Left() + bounds.Width(), bounds.Top() + bounds.Height()),
			Point(bounds.Left() + bounds.Width(), bounds.Top()),
			Point(bounds.Left(), bounds.Top())
		};
		Debug::DrawLine(walls[0], walls[1]);
		Debug::DrawLine(walls[1], walls[2]);
		Debug::DrawLine(walls[2], walls[3]);
		Debug::DrawLine(walls[3], walls[4]);

		int closestWallIndex = -1;

		Point steeringForce, point, closestPoint;

		for (auto& feeler : feelers) {
			for (int wallIndex = 0; wallIndex < 4; wallIndex++) {
				if (spic::GeneralHelper::LineIntersection(top,
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

	Point ForceDriven::ObstacleAvoidance()
	{
		Point location = Transform()->position;
		float radius = GetComponent<Collider>()->Size().x / 2;
		float realBoxLength = boxLength;

		std::shared_ptr<GameObject> closestIntersectingObstacle = NULL;

		//this will be used to track the distance to the CIB
		float distToClosestIP = MaxFloat;

		//this will record the transformed local coordinates of the CIB
		Point localPosOfClosestObstacle;

		for(const auto& obstacle: obstacles)
		{
			Point obstacleLocation = obstacle->Transform()->position;
			float obstacleRadius = obstacle->GetComponent<Collider>()->Size().x / 2;
			Point to = obstacleLocation - location;

			float range = realBoxLength + obstacleRadius;

			//if entity within range, tag for further consideration. (working in
			//distance-squared space to avoid sqrts)
			if ((to.LengthSq() < range * range))
			{

				//calculate this obstacle's position in local space
				Point localPos = PointToLocalSpace(obstacleLocation,
					heading,
					heading.Perp(),
					location);

				//if the local position has a negative x value then it must lay
				//behind the agent. (in which case it can be ignored)
				if (localPos.x >= 0)
				{
					//if the distance from the x axis to the object's position is less
					//than its radius + half the width of the detection box then there
					//is a potential intersection.
					float expandedRadius = obstacleRadius + radius;

					/*if (fabs(LocalPos.y) < ExpandedRadius)
					{*/
					//now to do a line/circle intersection test. The center of the 
					//circle is represented by (cX, cY). The intersection points are 
					//given by the formula x = cX +/-sqrt(r^2-cY^2) for y=0. 
					//We only need to look at the smallest positive value of x because
					//that will be the closest point of intersection.
					float cX = localPos.x;
					float cY = localPos.y;

					//we only need to calculate the sqrt part of the above equation once
					float SqrtPart = sqrt(expandedRadius * expandedRadius - cY * cY);

					float ip = cX - SqrtPart;

					if (ip <= 0.0)
					{
						ip = cX + SqrtPart;
					}

					//test to see if this is the closest so far. If it is keep a
					//record of the obstacle and its local coordinates
					if (ip < distToClosestIP)
					{
						distToClosestIP = ip;

						closestIntersectingObstacle = obstacle;

						localPosOfClosestObstacle = localPos;
					}
				}
			}
		}

		//if we have found an intersecting obstacle, calculate a steering 
		//force away from it
		Point steeringForce;

		if (closestIntersectingObstacle)
		{
			//the closer the agent is to an object, the stronger the 
			//steering force should be
			float multiplier = 1.0f + (boxLength - localPosOfClosestObstacle.x) /
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
			heading.Perp());
	}

	Point ForceDriven::Seperate()
	{
		Point steeringForce;
		for (const auto& neighbor : neighbors) {
			Point toAgent = Transform()->position - neighbor->Transform()->position;
			const float distance = toAgent.Length();

			if (distance > 0.0f && distance < desiredSeparation) {
				toAgent.Normalize();
				steeringForce += toAgent / toAgent.Length();
			}
		}
		return steeringForce;
	}

	Point ForceDriven::Align()
	{
		Point averageHeading;
		float neighborCount = static_cast<float>(neighbors.size());
		for (const auto& neighbor : neighbors) {
			averageHeading += neighbor->Heading();
		}
		if (neighborCount > 0.0f)
		{
			averageHeading /= neighborCount;
			averageHeading -= Velocity();
		}
		return averageHeading;
	}

	Point ForceDriven::Cohere()
	{
		Point centerOfMass, steeringForce;
		float neighborCount = static_cast<float>(neighbors.size());

		for (const auto& neighbor : neighbors) {
			centerOfMass += neighbor->Transform()->position;
		}
		if (neighborCount > 0.0f)
		{
			centerOfMass /= neighborCount;
			steeringForce = Seek(centerOfMass);
		}
		return steeringForce;
	}

	void ForceDriven::ApplyForce(Point& force) {
		this->GetComponent<RigidBody>()->AddForce(force / Mass());
		const float rotationInDeg = Velocity().Rotation();
		const float desiredRotation = spic::GeneralHelper::DEG2RAD<float>(rotationInDeg);
		const float angle = abs(this->Transform()->rotation - desiredRotation);
		if (angle >= this->angleSensitivity) {
			Transform()->rotation = desiredRotation;
			heading = { sin(desiredRotation), -cosf(desiredRotation) };
		}
	}
}