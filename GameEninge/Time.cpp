#include "Time.hpp"
#include "InternalTime.hpp"

using namespace spic;

double Time::deltaTime {0.0};
float Time::timeScale {1.0};


double spic::Time::DeltaTime()
{
    using namespace spic::internal::time;

    Time::deltaTime = InternalTime::deltaTime;

    return Time::deltaTime;
}

float spic::Time::TimeScale()
{
    return spic::Time::timeScale;
}

void spic::Time::TimeScale(const float newTimeScale)
{
    Time::timeScale = newTimeScale;
}
