#ifndef TIMER_H_
#define TIMER_H_

#include <chrono>
#include <functional>
#include <cstdio>
#include <atomic>
#include "ThreadWrapper.hpp"

namespace spic 
{
	/**
	 * @brief Timer class calls given function every x milliseconds
	*/
	class Timer {
	public:
		/**
		 * @brief Delay between every function call.
		*/
		typedef std::chrono::milliseconds Interval;

		/**
		 * @brief Function that is called after every interval.
		*/
		typedef std::function<void(void)> Timeout;

		/*
		 * @brief Destructor stops thread
		*/
		~Timer();

		/**
		 * @brief Starts timer.
		 * @param interval Delay between every function call.
		 * @param timeout Function that is called after every interval.
		*/
		void Start(const Interval& interval, const Timeout& timeout);

		/**
		 * @brief Stops timer
		*/
		void Stop() noexcept;
	private:
		std::unique_ptr<ThreadWrapper> threadWrapper;
		std::atomic_bool mRunning{};
	};
}

#endif // TIMER_H_