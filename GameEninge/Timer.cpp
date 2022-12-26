#include "Timer.hpp"

namespace spic
{
	Timer::~Timer() {
		if (mRunning)
			Stop();
	}

	void Timer::Start(const Interval& interval, const Timeout& timeout)
	{
		mRunning = true;

		threadWrapper = std::make_unique<ThreadWrapper>([this, interval, timeout]
			{
				while (mRunning) 
				{
					std::this_thread::sleep_for(interval);

					timeout();
				}
			});
	}

	void Timer::Stop() noexcept
	{
		mRunning = false;
	}
}