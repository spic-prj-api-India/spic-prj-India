#include "Flock.hpp"
#include "RigidBody.hpp"

namespace spic {
	Flock::Flock(const spic::FlockBehaviour flockBehaviour, const float maxSteeringForce, const float maxSpeed) : GameObject(),
		flockBehaviour{ flockBehaviour }, maxSteeringForce{ maxSteeringForce }, maxSpeed{ maxSpeed },
		paused{ true }, useWallAvoidance{ false }, useObstacleAvoidance{ false },
		useSeperation{ false }, useAlignment{ false }, useCohesion{ false }, useTarget{ false }
	{
	}

	float Flock::Heading()
	{
		std::shared_ptr<RigidBody> body = this->GetComponent<RigidBody>();
		Point velocity = body->Velocity();
		return velocity.Normalize();
	}

	void Flock::Target(std::unique_ptr<Point> newTarget, const float targetWeight)
	{
		this->useTarget = true;
		this->target = std::move(newTarget);
		this->targetWeight = targetWeight;
	}

	void Flock::Target(std::unique_ptr<Point> newTarget)
	{
		this->useTarget = true;
		this->target = std::move(newTarget);
		this->targetWeight = 1.0f;
	}

	void Flock::WallAvoidance(const float wallAvoidanceWeight, const float width, const float height)
	{
		this->useWallAvoidance = true;
		this->wallAvoidanceWeight = wallAvoidanceWeight;
		this->width = width;
		this->height = height;
	}

	void Flock::ObstacleAvoidance(const float obstacleAvoidanceWeight, const float feelerTreshold)
	{
		this->useObstacleAvoidance = true;
		this->obstacleAvoidanceWeight = obstacleAvoidanceWeight;
		this->feelerTreshold = feelerTreshold;
	}

	void Flock::Seperation(const float seperationWeight)
	{
		this->useSeperation = true;
		this->seperationWeight = seperationWeight;
	}

	void Flock::Alignment(const float alignmentWeight)
	{
		this->useAlignment = true;
		this->alignmentWeight = alignmentWeight;
	}

	void Flock::Cohesion(const float cohesionWeight)
	{
		this->useCohesion = true;
		this->cohesionWeight = cohesionWeight;
	}

	void Flock::StartFlock()
	{
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
				force = Arrival(*target.get()) * targetWeight;
				break;
			case FlockBehaviour::FLEE:
				force = Flee(*target.get()) * targetWeight;
				break;
			case FlockBehaviour::SEEK:
				force = Seek(*target.get()) * targetWeight;
				break;
			case FlockBehaviour::WANDER:
				force = Wander(*target.get()) * targetWeight;
				break;
			}
			if (!steeringForce.Accumulate(force, maxSteeringForce)) return steeringForce;
		}
		return steeringForce;
	}

	Point Flock::Seek(Point& target)
	{
		// Game object info
		Point location = this->Transform()->position;
		std::shared_ptr<RigidBody> body = this->GetComponent<RigidBody>();

		Point desired = target - location;

		if (desired.Length() == 0.0f) return Point(0.0f, 0.0f);

		desired.Normalize();
		desired *= maxSpeed;

		Point steeringForce = desired - body->Velocity();
		return steeringForce * body->Mass();
	}

	Point Flock::Flee(Point& target)
	{
		return {};
	}

	Point Flock::Arrival(Point& target)
	{
		return {};
	}

	Point Flock::Wander(Point& target)
	{
		return {};
	}

	Point Flock::WallAvoidance()
	{
		return {};
	}

	Point Flock::ObstacleAvoidance()
	{
		return {};
	}

	Point Flock::Seperate(const std::vector<std::shared_ptr<Flock>>& flocks)
	{
		Point steeringForce;
		for (const auto& flock : flocks) {
			if (flock.get() != this) {
				Point toAgent = Transform()->position - flock->Transform()->position;

				toAgent.Normalize();
				steeringForce += toAgent / toAgent.Length();

			}
		}
		return steeringForce;
	}

	Point Flock::Align(const std::vector<std::shared_ptr<Flock>>& flocks)
	{
		Point averageHeading;
		float neighborCount = 0.0f;
		for (const auto& flock : flocks) {
			if (flock.get() != this) {
				averageHeading += flock->Heading();
				neighborCount++;
			}
		}
		if (neighborCount > 0.0f)
		{
			averageHeading /= neighborCount;
			averageHeading -= Heading();
		}
		return averageHeading;
	}

	Point Flock::Cohere(const std::vector<std::shared_ptr<Flock>>& flocks)
	{
		Point centerOfMass, steeringForce;
		float neighborCount = 0.0f;

		for (const auto& flock : flocks) {
			if (flock.get() != this) {
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

	void Flock::ApplyForce(const Point& force) {
		this->GetComponent<RigidBody>()->AddForce(force);
	}
}