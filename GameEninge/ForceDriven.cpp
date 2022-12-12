#include "ForceDriven.hpp"
#include "RigidBody.hpp"
#include "GeneralHelper.hpp"
#include "Defaults.hpp"
#include "Transformations.hpp"
#include "Random.hpp"

using namespace spic::internal::math;

namespace spic {
	ForceDriven::ForceDriven(SumMethod sumMethod, const float maxSteeringForce, const float maxSpeed, const float angleSensitivity) : GameObject(),
		sumMethod{ sumMethod }, maxSteeringForce{ maxSteeringForce }, maxSpeed{ maxSpeed },
		angleSensitivity{ angleSensitivity }, paused{ true }, useWallAvoidance{ false },
		useObstacleAvoidance{ false }, useSeperation{ false }, useAlignment{ false },
		useCohesion{ false }, useTarget{ false }
	{
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

	void ForceDriven::Target(const Point& newTarget, const float targetWeight)
	{
		this->useTarget = true;
		this->target = newTarget;
		this->targetWeight = targetWeight;
	}

	void ForceDriven::Target(const Point& newTarget)
	{
		this->target = newTarget;
	}

	void ForceDriven::UseSeek()
	{
		this->steeringBehaviour = SteeringBehaviour::SEEK;
	}

	void ForceDriven::UseFlee()
	{
		this->steeringBehaviour = SteeringBehaviour::FLEE;
	}

	void ForceDriven::UseArrival(Deceleration deceleration)
	{
		this->steeringBehaviour = SteeringBehaviour::ARRIVAL;
		this->deceleration = deceleration;
	}

	void ForceDriven::UseWander(const float wanderRadius, const float wanderDistance, const float wanderJitter)
	{
		this->steeringBehaviour = SteeringBehaviour::WANDER;
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

	void ForceDriven::ObstacleAvoidance(const float obstacleAvoidanceWeight, const float feelerLength)
	{
		this->useObstacleAvoidance = true;
		this->obstacleAvoidanceWeight = obstacleAvoidanceWeight;
		this->feelerLength = feelerLength;
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
		if (steeringBehaviour < SteeringBehaviour::SEEK || steeringBehaviour > SteeringBehaviour::WANDER)
			throw std::exception("Steering behaviour needs to be defined");
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
		if (useTarget)
		{
			switch (steeringBehaviour) {
			case SteeringBehaviour::ARRIVAL:
				force = Arrival(target) * targetWeight;
				break;
			case SteeringBehaviour::FLEE:
				force = Flee(target) * targetWeight;
				break;
			case SteeringBehaviour::SEEK:
				force = Seek(target) * targetWeight;
				break;
			case SteeringBehaviour::WANDER:
				force = Wander() * targetWeight;
				break;
			}
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
		if (useTarget)
		{
			switch (steeringBehaviour) {
			case SteeringBehaviour::ARRIVAL:
				force = Arrival(target) * targetWeight;
				break;
			case SteeringBehaviour::FLEE:
				force = Flee(target) * targetWeight;
				break;
			case SteeringBehaviour::SEEK:
				force = Seek(target) * targetWeight;
				break;
			case SteeringBehaviour::WANDER:
				force = Wander() * targetWeight;
				break;
			}
			if (!steeringForce.Accumulate(force, maxSteeringForce)) return steeringForce;
		}
		return steeringForce;
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

		target += Point(RandomClamped() * wanderJitter,
			RandomClamped() * wanderJitter);

		target.Normalize();

		target *= wanderRadius;

		Point targetLocal = target + Point(wanderDistance, 0.0f);

		Point targetWorld = PointToWorldSpace(targetLocal,
			heading,
			heading.Side(),
			location);
		return targetWorld - location;
	}

	Point ForceDriven::WallAvoidance()
	{
		std::vector<Point> feelers(3);

		feelers[0] = Transform()->position + (heading * wallDetectionFeelerLength);

		Point temp = heading;
		RotateAroundOrigin(temp, spic::internal::Defaults::HALF_PI * 3.5f);
		feelers[1] = Transform()->position + (heading * (wallDetectionFeelerLength / 2.0f)) * temp;

		temp = heading;
		RotateAroundOrigin(temp, spic::internal::Defaults::HALF_PI * 0.5f);
		feelers[2] = Transform()->position + (heading * (wallDetectionFeelerLength / 2.0f)) * temp;

		float distToThisIP = 0.0;
		float distToClosestIP = std::numeric_limits<float>::max();

		Point walls[5] = { Point(bounds.Left(), bounds.Top()),
			Point(bounds.Left(), bounds.Top() + bounds.Height()),
			Point(bounds.Left() + bounds.Width(), bounds.Top() + bounds.Height()),
			Point(bounds.Left() + bounds.Width(), bounds.Top()),
			Point(bounds.Left(), bounds.Top())
		};

		int closestWallIndex = -1;

		Point steeringForce, point, closestPoint;

		for (auto& feeler : feelers) {
			for (int wallIndex = 0; wallIndex < 4; wallIndex++) {
				if (spic::GeneralHelper::LineIntersection(Transform()->position,
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
		//float realBoxLength = m_dDBoxLength;

		//GameObject* closestIntersectingObstacle = NULL;

		////this will be used to track the distance to the CIB
		//float distToClosestIP = MaxFloat;

		////this will record the transformed local coordinates of the CIB
		//Point localPosOfClosestObstacle;

		//while (curOb != endOb)
		//{

		//	Obstacle* obst = (*curOb);

		//	Point to = obst->Pos() - Transform()->position;

		//	double range = realBoxLength + obst->BRadius();

		//	//if entity within range, tag for further consideration. (working in
		//	//distance-squared space to avoid sqrts)
		//	if ((to.LengthSq() < range * range))
		//	{

		//		//calculate this obstacle's position in local space
		//		Point LocalPos = PointToLocalSpace(obst->Pos(),
		//			heading,
		//			Transform()->position);

		//		//if the local position has a negative x value then it must lay
		//		//behind the agent. (in which case it can be ignored)
		//		if (LocalPos.x >= 0)
		//		{
		//			//if the distance from the x axis to the object's position is less
		//			//than its radius + half the width of the detection box then there
		//			//is a potential intersection.
		//			double ExpandedRadius = obst->BRadius() + m_pMovingEntity->BRadius();

		//			/*if (fabs(LocalPos.y) < ExpandedRadius)
		//			{*/
		//			//now to do a line/circle intersection test. The center of the 
		//			//circle is represented by (cX, cY). The intersection points are 
		//			//given by the formula x = cX +/-sqrt(r^2-cY^2) for y=0. 
		//			//We only need to look at the smallest positive value of x because
		//			//that will be the closest point of intersection.
		//			double cX = LocalPos.x;
		//			double cY = LocalPos.y;

		//			//we only need to calculate the sqrt part of the above equation once
		//			double SqrtPart = sqrt(ExpandedRadius * ExpandedRadius - cY * cY);

		//			double ip = cX - SqrtPart;

		//			if (ip <= 0.0)
		//			{
		//				ip = cX + SqrtPart;
		//			}

		//			//test to see if this is the closest so far. If it is keep a
		//			//record of the obstacle and its local coordinates
		//			if (ip < distToClosestIP)
		//			{
		//				distToClosestIP = ip;

		//				closestIntersectingObstacle = obst;

		//				localPosOfClosestObstacle = LocalPos;
		//			}
		//		}
		//		//}
		//	}

		//	++curOb;
		//}

		////if we have found an intersecting obstacle, calculate a steering 
		////force away from it
		//Point steeringForce;

		//if (closestIntersectingObstacle)
		//{
		//	//the closer the agent is to an object, the stronger the 
		//	//steering force should be
		//	float multiplier = 1.0 + (m_dDBoxLength - localPosOfClosestObstacle.x) /
		//		m_dDBoxLength;

		//	//calculate the lateral force
		//	steeringForce.y = (closestIntersectingObstacle->BRadius() -
		//		localPosOfClosestObstacle.y) * multiplier;

		//	//apply a braking force proportional to the obstacles distance from
		//	//the MovingEntity. 
		//	const float brakingWeight = 0.2f;

		//	steeringForce.x = (closestIntersectingObstacle->BRadius() -
		//		localPosOfClosestObstacle.x) *
		//		brakingWeight;
		//}

		////finally, convert the steering vector from local to world space
		//return VectorToWorldSpace(steeringForce,
		//	heading);
		return {};
	}

	Point ForceDriven::Seperate()
	{
		Point steeringForce;
		for (const auto& neighbor : neighbors) {
			Point toAgent = Transform()->position - neighbor->Transform()->position;
			const float distance = toAgent.Length();

			if (distance > 0.0f && distance < desiredSeparation) {
				toAgent.Normalize();
				steeringForce += toAgent / distance;
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
		const float desiredRotation = spic::GeneralHelper::DEG2RAD<float>(Velocity().Rotation());
		const float angle = abs(this->Transform()->rotation - desiredRotation);
		if (angle >= this->angleSensitivity) {
			Transform()->rotation = desiredRotation;
			heading = { cosf(desiredRotation) , sin(desiredRotation) };
		}
	}
}