#include "Pathfinding.hpp"
#include "GameEngine.hpp"
#include "PhysicsExtension1.hpp"
#include "GameEngineInfo.hpp"
#include "RigidBody.hpp"

namespace spic {
	Pathfinding::Pathfinding(const std::shared_ptr<spic::GameObject> target,
		const float pathFindingWeight, const float obstacleAvoidanceWeight, const float feelerTreshold) :
		target{ target }, pathFindingWeight{ pathFindingWeight },
		obstacleAvoidanceWeight{ obstacleAvoidanceWeight }, feelerTreshold{ feelerTreshold }, paused{ true }
	{
	}

	void Pathfinding::Target(const std::shared_ptr<spic::GameObject> newTarget)
	{
		this->target = newTarget;
	}

	void Pathfinding::Start()
	{
		if (target == nullptr)
			throw std::exception("Target needs to be defined");
		paused = false;
	}

	void Pathfinding::Update()
	{
		if (paused)
			return;
		Point steeringForce;
		steeringForce += Path() * pathFindingWeight;
		steeringForce += ObstacleAvoidance() * obstacleAvoidanceWeight;
		ApplyForce(steeringForce);
	}

	void Pathfinding::Stop()
	{
		paused = true;
	}

	Point Pathfinding::Path()
	{
		// Game object info
		Point position = this->gameObject->Transform()->position;
		std::shared_ptr<RigidBody> body = this->gameObject->GetComponent<RigidBody>();

		// Target info
		Point targetPosition = target->Transform()->position;
		const float targetSpeed = 0.0f;

		Point direction = targetPosition - gameObject->Transform()->position;
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

	Point Pathfinding::ObstacleAvoidance()
	{
		return Point();
	}

	void Pathfinding::ApplyForce(const Point& force) {
		GameEngine* engine = GameEngine::GetInstance();
		const bool exists = engine->HasExtension<extensions::PhysicsExtension1>();
		if (!exists)
			return;
		std::weak_ptr<extensions::PhysicsExtension1> physicsExtension = engine->GetExtension<extensions::PhysicsExtension1>();
		if (const auto& box2DExtension = physicsExtension.lock())
			box2DExtension->AddForce(this->gameObject->Name(), force);
	}
}