#include "ForceDriven.hpp"
#include "Flocking.hpp"
#include "Steering.hpp"
#include "RigidBody.hpp"
#include "GeneralHelper.hpp"
#include "Time.hpp"
#include "Matrix.hpp"

namespace spic
{
	ForceDriven::ForceDriven(SumMethod sumMethod, const float maxSteeringForce,
		const float maxSpeed, const float maxTurnRate, const float boundingRadius) : GameObject(),
		sumMethod{ sumMethod }, maxSteeringForce{ maxSteeringForce }, maxSpeed{ maxSpeed },
		maxTurnRate{ maxTurnRate }, boundingRadius{ boundingRadius }, paused{ true }
	{
		heading = { sinf(Transform()->rotation), -cosf(Transform()->rotation) };
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

	Point ForceDriven::Side() const
	{
		return heading.Perp();
	}

	float ForceDriven::Mass() const
	{
		std::shared_ptr<RigidBody> body = this->GetComponent<RigidBody>();
		return body->Mass();
	}

	float ForceDriven::BRadius() const
	{
		return boundingRadius;
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
		/*const double dt = spic::Time::DeltaTime();
		force *= static_cast<float>(dt);
		force.Truncate(maxSpeed);*/
		//RotateHeadingToFacePosition(force);
		this->GetComponent<RigidBody>()->AddForce(force / Mass());

		const float rotationInDeg = Velocity().Rotation();
		const float desiredRotation = spic::helper_functions::general_helper::DEG2RAD<float>(rotationInDeg);
		const float angle = fabs(this->Transform()->rotation - desiredRotation);
		heading = { sinf(desiredRotation), -cosf(desiredRotation) };
		/*if (angle >= this->maxTurnRate) {*/
			Transform()->rotation = desiredRotation;
		//}
		/*const float currentAngle = Transform()->rotation;
		const float rotationInDeg = Velocity().Rotation();
		const float desiredAngle = spic::helper_functions::general_helper::DEG2RAD<float>(rotationInDeg);
		float desiredRotation = desiredAngle - currentAngle;
		float newAngle = currentAngle + fmin(this->maxTurnRate, fmax(-this->maxTurnRate, desiredRotation));
		Transform()->rotation = newAngle;
		heading = { sinf(newAngle), -cosf(newAngle) };
		if (newAngle >= this->maxTurnRate) {
			Transform()->rotation = desiredRotation;
		}*/
	}

	bool ForceDriven::RotateHeadingToFacePosition(Point& force)
	{
		Point toTarget = force - Transform()->position;
		toTarget.Normalize();

		//first determine the angle between the heading vector and the target
		float angle = acos(heading.Dot(toTarget));

		//return true if the player is facing the target
		if (angle < 0.00001f) return true;

		//clamp the amount to turn to the max turn rate
		if (fabs(angle) > maxTurnRate) angle = maxTurnRate;

		return RotateHeadingByAngle(angle * heading.Sign(toTarget), force);
	}

	//----------------------------- RotateHeadingByAngle --------------------------
	//
	// This method rotates the entity's heading and side vectors by an amount
	//
	//  returns true when the heading is facing in the desired direction
	//-----------------------------------------------------------------------------
	bool ForceDriven::RotateHeadingByAngle(float angle, Point& force)
	{
		//The next few lines use a rotation matrix to rotate the player's heading
		//vector accordingly
		spic::internal::math::S2DMatrix RotationMatrix;
		RotationMatrix.Rotate(angle);
		RotationMatrix.TransformPoints(heading);
		RotationMatrix.TransformPoints(force);

		return false;

	}
}