#ifndef INTERNALTIME_H_
#define INTERNALTIME_H_

#include <ctime>

namespace spic::internal::time
{

	struct InternalTime
	{
		static clock_t beginFrame;
		static clock_t endFrame;
		static clock_t deltaTime;
		static unsigned int frames;
		static double frameRate;
		static double  averageFrameTimeMilliseconds;

		static void SetStartValues();
	
		static void BeginFrame();

		static void EndFrame();
	};
}
#endif