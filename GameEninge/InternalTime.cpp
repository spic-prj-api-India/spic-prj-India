#include "InternalTime.hpp"

using spic::internal::time::InternalTime;

clock_t InternalTime::beginFrame;
clock_t InternalTime::endFrame;
clock_t InternalTime::deltaTime;
unsigned int InternalTime::frames;
double InternalTime::frameRate;
double  InternalTime::averageFrameTimeMilliseconds;

double clockToMilliseconds(clock_t ticks) {
		// units/(units/time) => time (seconds) * 1000 = milliseconds
		return (ticks / (double)CLOCKS_PER_SEC) * 1000.0;
}

void spic::internal::time::InternalTime::SetStartValues()
{
	deltaTime = 0;
	frames = 0;
	frameRate = 30;
	averageFrameTimeMilliseconds = 33.333;
}

void spic::internal::time::InternalTime::EndFrame()
{
	endFrame = clock();

	deltaTime += endFrame - beginFrame;
	frames++;

	//if you really want fps
	if (clockToMilliseconds(deltaTime) > 1000.0) { //every second
		frameRate = (double)frames * 0.5 + frameRate * 0.5; //more stable
		frames = 0;
		deltaTime -= CLOCKS_PER_SEC;
		averageFrameTimeMilliseconds = 1000.0 / (frameRate == 0 ? 0.001 : frameRate);
	}
}

void spic::internal::time::InternalTime::BeginFrame()
{
	beginFrame = clock();
}
