#include "ISystem.hpp"
#include "InternalTime.hpp"
#include "Time.hpp"
#include "Settings.hpp"

void spic::internal::systems::ISystem::CanUpdate()
{
	this->stepsAmount = 0;

	// get current time double
	auto currentTime = spic::internal::time::InternalTime::TickInMilliseconds() / CLOCKS_PER_SEC;

	if (currentTime - this->lastTickTime > 5)
		this->lastTickTime = currentTime;

	this->accumultator += (currentTime - this->lastTickTime) * spic::Time::TimeScale();

	while (this->accumultator > spic::settings::K_SECONDS_PER_UPDATE)
	{
		this->accumultator -= spic::settings::K_SECONDS_PER_UPDATE;
		++this->stepsAmount;
	}

	this->lastTickTime = currentTime;
}

void spic::internal::systems::ISystem::RestartTiming()
{
	this->accumultator = 0;
	this->lastTickTime = 0;
}
