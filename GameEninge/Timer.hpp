#ifndef TIMER_H_
#define TIMER_H_

#include <chrono>
#include <functional>
#include <cstdio>
#include <atomic>
#include "ThreadWrapper.hpp"

namespace spic 
{
	class Timer {
	public:
		typedef std::chrono::milliseconds Interval;
		typedef std::function<void(void)> Timeout;

		~Timer();

		void Start(const Interval& interval, const Timeout& timeout);

		void Stop() noexcept;
	private:
		std::unique_ptr<ThreadWrapper> threadWrapper;
		std::atomic_bool mRunning{};
	};
}

#endif // TIMER_H_