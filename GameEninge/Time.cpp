#include "Time.hpp"

using namespace spic;

float Time::deltaTime {0.0};
float Time::timeScale {1.0};

float spic::Time::DeltaTime()
{
    //TODO
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
