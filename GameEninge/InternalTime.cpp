#include "InternalTime.hpp"
#include <chrono>
#include <thread>

using spic::internal::time::InternalTime;

clock_t InternalTime::beginFrame;
clock_t InternalTime::endFrame;
clock_t InternalTime::deltaTime;
unsigned int InternalTime::frames;
double InternalTime::frameRate;
double  InternalTime::averageFrameTimeMilliseconds;

void spic::internal::time::InternalTime::SetStartValues()
{
	deltaTime = 0;
	frames = 0;
	frameRate = 60;
	averageFrameTimeMilliseconds = 16.6;
}

void spic::internal::time::InternalTime::EndFrame()
{
	endFrame = clock();

	deltaTime += endFrame - beginFrame;
	frames++;

	if (InternalTime::clockToMilliseconds(deltaTime) > 1000.0) //every second
	{ 
		frameRate = (double)frames * 0.5 + frameRate * 0.5; //more stable framerate
		frames = 0;
		deltaTime -= CLOCKS_PER_SEC;
		averageFrameTimeMilliseconds = 1000.0 / (frameRate == 0 ? 0.001 : frameRate); // second / framerate
	}
}

void spic::internal::time::InternalTime::Delay()
{
	// 1000 ms <=> 1 s
	if ((InternalTime::frameRate > 0) && ((InternalTime::deltaTime) < (1000.0 / InternalTime::frameRate)))
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(InternalTime::deltaTime));
	}
}

double spic::internal::time::InternalTime::TickNow()
{
	return InternalTime::clockToMilliseconds(clock());
}

void spic::internal::time::InternalTime::BeginFrame()
{
	beginFrame = clock();
}
