#include "Flock.hpp"
#include "GameEngine.hpp"
#include "PhysicsExtension1.hpp"
#include "GameEngineInfo.hpp"
#include "RigidBody.hpp"

namespace spic {
	Flock::Flock(const spic::FlockBehaviour flockBehaviour, const std::shared_ptr<spic::GameObject> target, const float maxSteeringForce,
		const float maxSpeed, const float flockWeight) : GameObject(),
		flockBehaviour{ flockBehaviour }, target{ target }, maxSteeringForce{ maxSteeringForce },
		maxSpeed{ maxSpeed }, flockBehaviourWeight{ flockBehaviourWeight }, paused{ true },
		useWallAvoidance{ false }, useObstacleAvoidance{ false }, useSeperation{ false },
		useAlignment{ false }, useCohesion{ false }
	{
	}

	void Flock::Target(const std::shared_ptr<spic::GameObject> newTarget)
	{
		this->target = newTarget;
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
		if (target == nullptr)
			throw std::exception("Target needs to be defined");
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
		switch (flockBehaviour) {
		case FlockBehaviour::ARRIVAL:
			force = Arrival() * flockBehaviourWeight;
			break;
		case FlockBehaviour::FLEE:
			force = Flee() * flockBehaviourWeight;
			break;
		case FlockBehaviour::SEEK:
			force = Seek() * flockBehaviourWeight;
			break;
		case FlockBehaviour::WANDER:
			force = Wander() * flockBehaviourWeight;
			break;
		}
		if (!steeringForce.Accumulate(force, maxSteeringForce)) return steeringForce;
		return steeringForce;
	}

	Point Flock::Seek()
	{
		// Game object info
		Point position = this->Transform()->position;
		std::shared_ptr<RigidBody> body = this->GetComponent<RigidBody>();

		// Target info
		Point targetPosition = target->Transform()->position;
		const float targetSpeed = 1.0f;

		Point direction = targetPosition - position;
		const float distanceToTravel = direction.Normalize();

		// For most of the movement, the target speed is ok
		float speedToUse = targetSpeed;

		// Check if this speed will cause overshoot in the next time step.
		// If so, we need to scale the speed down to just enough to reach
		// the target point. (Assuming here a step length based on 60 fps)
		const float distancePerTimestep = speedToUse / FPS;
		if (distancePerTimestep > distanceToTravel)
			speedToUse *= (distanceToTravel / distancePerTimestep);

		// The rest is pretty much what you had already:
		Point desiredVelocity = direction * speedToUse;
		Point changeInVelocity = desiredVelocity - body->Velocity();

		return changeInVelocity * body->Mass() * FPS;
	}

	Point Flock::Flee()
	{
		return {};
	}

	Point Flock::Arrival()
	{
		return {};
	}

	Point Flock::Wander()
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
		return {};
	}
	Point Flock::Align(const std::vector<std::shared_ptr<Flock>>& flocks)
	{
		return {};
	}
	Point Flock::Cohere(const std::vector<std::shared_ptr<Flock>>& flocks)
	{
		return {};
	}

	void Flock::ApplyForce(const Point& force) {
		GameEngine* engine = GameEngine::GetInstance();
		const bool exists = engine->HasExtension<extensions::PhysicsExtension1>();
		if (!exists)
			return;
		std::weak_ptr<extensions::PhysicsExtension1> physicsExtension = engine->GetExtension<extensions::PhysicsExtension1>();
		if (const auto& box2DExtension = physicsExtension.lock())
			box2DExtension->AddForce(this->Name(), force);
	}
}