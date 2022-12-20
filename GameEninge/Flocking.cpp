#include "Flocking.hpp"

namespace spic 
{
	Flocking::Flocking(ForceDriven* agent) : agent{ agent },
		useSeperation{ false }, useAlignment{ false }, useCohesion{ false }
	{
	}

	Flocking::Flocking(ForceDriven* agent, const float viewRadius, const  float seperationWeight,
		const float desiredSeparation, const float alignmentWeight, const float cohesionWeight) :
		useSeperation{ true }, useAlignment{ true }, useCohesion{ true }, agent{ agent },
		viewRadius{ viewRadius }, seperationWeight{ seperationWeight }, desiredSeparation{ desiredSeparation },
		alignmentWeight{ alignmentWeight }, cohesionWeight{ cohesionWeight }
	{
	}

	void Flocking::SeperationOn(const float seperationWeight, const float desiredSeparation)
	{
		this->useSeperation = true;
		this->seperationWeight = seperationWeight;
		this->desiredSeparation = desiredSeparation;
	}

	void Flocking::AlignmentOn(const float alignmentWeight, const float viewRadius)
	{
		this->useAlignment = true;
		this->alignmentWeight = alignmentWeight;
		this->viewRadius = viewRadius;
	}

	void Flocking::CohesionOn(const float cohesionWeight, const float viewRadius)
	{
		this->useCohesion = true;
		this->cohesionWeight = cohesionWeight;
		this->viewRadius = viewRadius;
	}

	void Flocking::TagNeighbors(const std::vector<std::shared_ptr<ForceDriven>>& forceDrivenEntities)
	{
		neighbors = {};
		for (const auto& forceDrivenEntity : forceDrivenEntities) {
			if (forceDrivenEntity.get() == this->agent)
				continue;
			const Point toAgent = this->agent->Transform()->position - forceDrivenEntity->Transform()->position;
			const float distance = toAgent.Length();

			if (distance > 0.0f && distance < viewRadius) {
				neighbors.emplace_back(forceDrivenEntity);
			}
		}
	}

	void Flocking::Calculate(std::function<bool(Point force)> addSteeringForceCallback)
	{
		Point force;
		if (useSeperation) {
			force = Seperate() * seperationWeight;
			if (!addSteeringForceCallback(force))
				return;
		}
		if (useAlignment) {
			force = Align() * alignmentWeight;
			if (!addSteeringForceCallback(force))
				return;
		}
		if (useCohesion) {
			force = Cohere() * cohesionWeight;
			if (!addSteeringForceCallback(force))
				return;
		}
	}

	Point Flocking::Seperate()
	{
		Point steeringForce;
		for (const auto& neighbor : neighbors) {
			Point toAgent = this->agent->Transform()->position - neighbor->Transform()->position;
			const float distance = toAgent.Length();

			if (distance > 0.0f && distance < desiredSeparation) {
				toAgent.Normalize();
				steeringForce += toAgent / toAgent.Length();
			}
		}
		return steeringForce;
	}

	Point Flocking::Align()
	{
		Point averageHeading;
		const float neighborCount = static_cast<float>(neighbors.size());
		for (const auto& neighbor : neighbors) {
			averageHeading += neighbor->Heading();
		}
		if (neighborCount > 0.0f)
		{
			averageHeading /= neighborCount;
			averageHeading -= this->agent->Velocity();
		}
		return averageHeading;
	}

	Point Flocking::Seek(Point target)
	{
		const Point& location = this->agent->Transform()->position;

		Point desiredVelocity = target - location;

		if (desiredVelocity.Length() == 0.0f)
			return {};

		desiredVelocity.Normalize();
		desiredVelocity *= this->agent->MaxSpeed();

		return (desiredVelocity - this->agent->Velocity());
	}

	Point Flocking::Cohere()
	{
		Point centerOfMass, steeringForce;
		const float neighborCount = static_cast<float>(neighbors.size());

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
}