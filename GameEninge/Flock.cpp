#include "Flock.hpp"
#include "RigidBody.hpp"
#include "GeneralHelper.hpp"
#include "Defaults.hpp"

namespace spic {
	Flock::Flock(SumMethod sumMethod, const float maxSteeringForce, const float maxSpeed, const float angleSensitivity) : GameObject(),
		sumMethod{ sumMethod }, maxSteeringForce{ maxSteeringForce }, maxSpeed{ maxSpeed },
		angleSensitivity{ angleSensitivity }, paused{ true }, useWallAvoidance{ false },
		useObstacleAvoidance{ false }, useSeperation{ false }, useAlignment{ false },
		useCohesion{ false }, useTarget{ false }
	{
	}

	Point Flock::Velocity() const
	{
		std::shared_ptr<RigidBody> body = this->GetComponent<RigidBody>();
		return body->Velocity();
	}

	float Flock::Mass() const
	{
		std::shared_ptr<RigidBody> body = this->GetComponent<RigidBody>();
		return body->Mass();
	}

	void Flock::Target(const Point& newTarget, const float targetWeight)
	{
		this->useTarget = true;
		this->target = newTarget;
		this->targetWeight = targetWeight;
	}

	void Flock::Target(const Point& newTarget)
	{
		this->target = newTarget;
	}

	void Flock::Seek()
	{
		this->flockBehaviour = FlockBehaviour::SEEK;
	}

	void Flock::Flee()
	{
		this->flockBehaviour = FlockBehaviour::FLEE;
	}

	void Flock::Arrival(Deceleration deceleration)
	{
		this->flockBehaviour = FlockBehaviour::ARRIVAL;
		this->deceleration = deceleration;
	}

	void Flock::Wander(const float wanderRadius, const float wanderDistance, const float wanderJitter)
	{
		this->flockBehaviour = FlockBehaviour::WANDER;
		this->wanderRadius = wanderRadius;
		this->wanderDistance = wanderDistance;
		this->wanderJitter = wanderJitter;
	}

	void Flock::WallAvoidance(const float wallAvoidanceWeight, const float wallDetectionFeelerLength, const Bounds& bounds)
	{
		this->useWallAvoidance = true;
		this->wallAvoidanceWeight = wallAvoidanceWeight;
		this->wallDetectionFeelerLength = wallDetectionFeelerLength;
		this->bounds = bounds;
	}

	void Flock::ObstacleAvoidance(const float obstacleAvoidanceWeight, const float feelerTreshold)
	{
		this->useObstacleAvoidance = true;
		this->obstacleAvoidanceWeight = obstacleAvoidanceWeight;
		this->feelerTreshold = feelerTreshold;
	}

	void Flock::Seperation(const float seperationWeight, const float desiredSeparation)
	{
		this->useSeperation = true;
		this->seperationWeight = seperationWeight;
		this->desiredSeparation = desiredSeparation;
	}

	void Flock::Alignment(const float alignmentWeight, const float viewRadius)
	{
		this->useAlignment = true;
		this->alignmentWeight = alignmentWeight;
		this->viewRadius = viewRadius;
	}

	void Flock::Cohesion(const float cohesionWeight, const float viewRadius)
	{
		this->useCohesion = true;
		this->cohesionWeight = cohesionWeight;
		this->viewRadius = viewRadius;
	}

	void Flock::StartFlock()
	{
		if (flockBehaviour < FlockBehaviour::SEEK || flockBehaviour > FlockBehaviour::WANDER)
			throw std::exception("Flock behaviour needs to be defined");
		paused = false;
	}

	void Flock::UpdateFlock(const std::vector<std::shared_ptr<Flock>>& flocks)
	{
		if (paused)
			return;
		Point steeringForce = Calculate(flocks);
		ApplyForce(steeringForce);
	}

	void Flock::StopFlock()
	{
		paused = true;
	}

	Point Flock::Calculate(const std::vector<std::shared_ptr<Flock>>& flocks)
	{
		switch (sumMethod) {
		case SumMethod::WEIGHTED_AVERAGE:
			return CalculateWeightedSum(flocks);

		case SumMethod::PRIORITIZED:
			return CalculatePrioritized(flocks);

		default:
			return {};
		}
	}

	Point Flock::CalculateWeightedSum(const std::vector<std::shared_ptr<Flock>>& flocks)
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
			force = Seperate(flocks) * seperationWeight;
			steeringForce += force;
		}
		if (useAlignment)
		{
			force = Align(flocks) * alignmentWeight;
			steeringForce += force;
		}
		if (useCohesion)
		{
			force = Cohere(flocks) * cohesionWeight;
			steeringForce += force;
		}
		if (useTarget)
		{
			switch (flockBehaviour) {
			case FlockBehaviour::ARRIVAL:
				force = Arrival(target) * targetWeight;
				break;
			case FlockBehaviour::FLEE:
				force = Flee(target) * targetWeight;
				break;
			case FlockBehaviour::SEEK:
				force = Seek(target) * targetWeight;
				break;
			case FlockBehaviour::WANDER:
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

	Point Flock::CalculatePrioritized(const std::vector<std::shared_ptr<Flock>>& flocks)
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
			force = Seperate(flocks) * seperationWeight;
			if (!steeringForce.Accumulate(force, maxSteeringForce)) return steeringForce;
		}
		if (useAlignment)
		{
			force = Align(flocks) * alignmentWeight;
			if (!steeringForce.Accumulate(force, maxSteeringForce)) return steeringForce;
		}
		if (useCohesion)
		{
			force = Cohere(flocks) * cohesionWeight;
			if (!steeringForce.Accumulate(force, maxSteeringForce)) return steeringForce;
		}
		if (useTarget)
		{
			switch (flockBehaviour) {
			case FlockBehaviour::ARRIVAL:
				force = Arrival(target) * targetWeight;
				break;
			case FlockBehaviour::FLEE:
				force = Flee(target) * targetWeight;
				break;
			case FlockBehaviour::SEEK:
				force = Seek(target) * targetWeight;
				break;
			case FlockBehaviour::WANDER:
				force = Wander() * targetWeight;
				break;
			}
			if (!steeringForce.Accumulate(force, maxSteeringForce)) return steeringForce;
		}
		return steeringForce;
	}

	Point Flock::Seek(Point target)
	{
		const Point& location = this->Transform()->position;

		Point desiredVelocity = target - location;

		if (desiredVelocity.Length() == 0.0f)
			return {};

		desiredVelocity.Normalize();
		desiredVelocity *= maxSpeed;

		return (desiredVelocity - Velocity());
	}

	Point Flock::Flee(Point target)
	{
		Point& location = this->Transform()->position;

		Point desiredVelocity = location - target;

		if (desiredVelocity.Length() == 0.0f)
			return {};

		desiredVelocity.Normalize();
		desiredVelocity *= maxSpeed;

		return (desiredVelocity - Velocity());
	}

	Point Flock::Arrival(Point target)
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

	Point Flock::Wander()
	{
		//Point target;
		//const Point& location = this->Transform()->position;

		//target += Point(RandomClamped() * wanderJitter,
		//	RandomClamped() * wanderJitter);

		//target.Normalize();

		//target *= wanderRadius;

		//Point targetLocal = target + Point(wanderDistance, 0.0f);
		////project the target into world space
		//Point targetWorld = PointToWorldSpace(targetLocal,
		//	location.Heading(),
		//	m_pVehicle->Side(),
		//	location);
		//return targetWorld - Transform()->position;
		return {};
	}

	Point Flock::WallAvoidance()
	{
		std::vector<Point> feelers(3);

		//feeler pointing straight in front
		feelers[0] = Transform()->position + (heading * wallDetectionFeelerLength);

		//feeler to left
		Point temp = heading;
		temp.Rotate(spic::internal::Defaults::HALF_PI * 3.5f);
		feelers[1] = Transform()->position + (heading * (wallDetectionFeelerLength / 2.0f)) * temp;

		//feeler to right
		temp = heading;
		temp.Rotate(spic::internal::Defaults::HALF_PI * 0.5f);
		feelers[2] = Transform()->position + (heading * (wallDetectionFeelerLength / 2.0f)) * temp;

		float distToThisIP = 0.0;
		float distToClosestIP = std::numeric_limits<float>::max();

		Point wallsv[5] = { Point(bounds.Left(), bounds.Top()),
			Point(bounds.Left(), bounds.Top() + bounds.Height()),
			Point(bounds.Left() + bounds.Width(), bounds.Top() + bounds.Height()),
			Point(bounds.Left() + bounds.Width(), bounds.Top()),
			Point(bounds.Left(), bounds.Top())
		};

		//this will hold an index into the vector of walls
		int closestWall = -1;

		Point steeringForce,
			point,         //used for storing temporary info
			closestPoint;  //holds the closest intersection point

		//examine each feeler in turn
		for (unsigned int flr = 0; flr < feelers.size(); ++flr) {

			//run through each wall checking for any intersection points
			for (int i = 0; i < 4; i++) {

				if (spic::GeneralHelper::LineIntersection(Transform()->position,
					feelers[flr],
					wallsv[i],
					wallsv[i + 1],
					point,
					distToThisIP))
				{
					//is this the closest found so far? If so keep a record
					if (distToThisIP < distToClosestIP)
					{
						distToClosestIP = distToThisIP;

						closestWall = i;

						closestPoint = point;
					}
				}
			}//next wall


			//if an intersection point has been detected, calculate a force  
			//that will direct the agent away
			if (closestWall != -1)
			{
				//calculate by what distance the projected position of the agent
				//will overshoot the wall
				Point overShoot = feelers[flr] - closestPoint;

				Point temp = (wallsv[closestWall] - wallsv[closestWall + 1]);
				temp.Normalize();
				Point normal(-temp.y, temp.x);

				//create a force in the direction of the wall normal, with a 
				//magnitude of the overshoot
				steeringForce = normal * overShoot.Length();
			}

		}//next feeler

		return steeringForce;
	}

	Point Flock::ObstacleAvoidance()
	{
		return {};
	}

	Point Flock::Seperate(const std::vector<std::shared_ptr<Flock>>& flocks)
	{
		Point steeringForce;
		for (const auto& flock : flocks) {
			if (flock.get() == this)
				continue;
			Point toAgent = Transform()->position - flock->Transform()->position;
			const float distance = toAgent.Length();

			if (distance > 0.0f && distance < desiredSeparation) {
				toAgent.Normalize();
				steeringForce += toAgent / distance;
			}
		}
		return steeringForce;
	}

	Point Flock::Align(const std::vector<std::shared_ptr<Flock>>& flocks)
	{
		Point averageHeading;
		float neighborCount = 0.0f;
		for (const auto& flock : flocks) {
			if (flock.get() == this)
				continue;
			Point toAgent = Transform()->position - flock->Transform()->position;
			const float distance = toAgent.Length();

			if (distance > 0.0f && distance < viewRadius) {
				averageHeading += flock->Velocity();
				neighborCount++;
			}
		}
		if (neighborCount > 0.0f)
		{
			averageHeading /= neighborCount;
			averageHeading -= Velocity();
		}
		return averageHeading;
	}

	Point Flock::Cohere(const std::vector<std::shared_ptr<Flock>>& flocks)
	{
		Point centerOfMass, steeringForce;
		float neighborCount = 0.0f;

		for (const auto& flock : flocks) {
			if (flock.get() == this)
				continue;
			Point toAgent = Transform()->position - flock->Transform()->position;
			const float distance = toAgent.Length();

			if (distance > 0.0f && distance < viewRadius) {
				centerOfMass += flock->Transform()->position;
				++neighborCount;
			}
		}
		if (neighborCount > 0.0f)
		{
			centerOfMass /= neighborCount;
			steeringForce = Seek(centerOfMass);
		}
		return steeringForce;
	}

	void Flock::ApplyForce(Point& force) {
		this->GetComponent<RigidBody>()->AddForce(force / Mass());
		const float desiredRotation = spic::GeneralHelper::DEG2RAD<float>(Velocity().Rotation());
		const float angle = abs(this->Transform()->rotation - desiredRotation);
		if (angle >= this->angleSensitivity) {
			Transform()->rotation = desiredRotation;
			heading = { cosf(desiredRotation) , sin(desiredRotation) };
		}
	}
}