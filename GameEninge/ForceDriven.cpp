#include "ForceDriven.hpp"
#include "RigidBody.hpp"
#include "GeneralHelper.hpp"
#include "Defaults.hpp"
#include "Transformations.hpp"
#include "Random.hpp"
#include <functional>
#include "Debug.hpp"
#include "Collider.hpp"
#include "Settings.hpp"
#include "Flocking.hpp"
#include "Steering.hpp"

using namespace spic::internal::math;

namespace spic {
	ForceDriven::ForceDriven(SumMethod sumMethod, const float maxSteeringForce, const float maxSpeed, const float angleSensitivity) : GameObject(),
		sumMethod{ sumMethod }, maxSteeringForce{ maxSteeringForce }, maxSpeed{ maxSpeed },
		angleSensitivity{ angleSensitivity }, paused{ true }
	{
	}

	Point ForceDriven::Velocity() const
	{
		std::shared_ptr<RigidBody> body = this->GetComponent<RigidBody>();
		return body->Velocity();
	}

	float ForceDriven::MaxSpeed() const
	{
		return this->maxSpeed;
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

	void ForceDriven::StartForceDrivenEntity()
	{
		paused = false;
	}

	void ForceDriven::UpdateForceDrivenEntity(const std::vector<std::shared_ptr<ForceDriven>>& forceDrivenEntities)
	{
		if (paused)
			return;
		const auto& flocking = GetComponent<Flocking>();
		if (flocking != nullptr)
			flocking->TagNeighbors(forceDrivenEntities);
		Point steeringForce = Calculate();
		ApplyForce(steeringForce);
	}

	void ForceDriven::StopForceDrivenEntity()
	{
		paused = true;
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

		auto addSteeringForceCallback = [this, &steeringForce](Point force) {
			steeringForce += force;
			return true;
		};
		const auto& steering = GetComponent<Steering>();
		if (steering != nullptr)
			steering->Calculate(addSteeringForceCallback);
		const auto& flocking = GetComponent<Flocking>();
		if (flocking != nullptr)
			flocking->Calculate(addSteeringForceCallback);
		if (steeringForce.Length() > maxSteeringForce) {
			steeringForce.Normalize();
			steeringForce *= maxSteeringForce;
		}
		return steeringForce;
	}

	Point ForceDriven::CalculatePrioritized()
	{
		Point steeringForce{};

		auto addSteeringForceCallback = [this, &steeringForce](Point force) {
			if (!steeringForce.Accumulate(force, maxSteeringForce)) return false;
			return true;
		};
		const auto& steering = GetComponent<Steering>();
		if (steering != nullptr)
			steering->Calculate(addSteeringForceCallback);
		const auto& flocking = GetComponent<Flocking>();
		if (flocking != nullptr)
			flocking->Calculate(addSteeringForceCallback);
		return steeringForce;
	}

	void ForceDriven::ApplyForce(Point& force) {
		this->GetComponent<RigidBody>()->AddForce(force / Mass());
		const float rotationInDeg = Velocity().Rotation();
		const float desiredRotation = spic::general_helper::DEG2RAD<float>(rotationInDeg);
		const float angle = abs(this->Transform()->rotation - desiredRotation);
		if (angle >= this->angleSensitivity) {
			Transform()->rotation = desiredRotation;
			heading = { sin(desiredRotation), -cosf(desiredRotation) };
		}
	}
}