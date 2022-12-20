#include "Time.hpp"
#include "InternalTime.hpp"

using namespace spic;

double Time::deltaTime {0.0};
double Time::timeScale {1.0};


double spic::Time::DeltaTime()
{
    using namespace spic::internal::time;

    Time::deltaTime = InternalTime::deltaTime;

    return Time::deltaTime;
}

double spic::Time::TimeScale()
{
    return spic::Time::timeScale;
}

void spic::Time::TimeScale(const double newTimeScale)
{
    if (newTimeScale < 0 || 2 < newTimeScale)
        return;

    Time::timeScale = newTimeScale;
}
