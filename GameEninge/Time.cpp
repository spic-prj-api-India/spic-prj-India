#include "Time.hpp"

using namespace spic;

double Time::deltaTime {0.0};
double Time::timeScale {1.0};

double spic::Time::DeltaTime()
{
    //TODO
    return Time::deltaTime;
}

double spic::Time::TimeScale()
{
    return spic::Time::timeScale;
}
