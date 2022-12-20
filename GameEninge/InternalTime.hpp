#ifndef INTERNALTIME_H_
#define INTERNALTIME_H_

#include <ctime>

/**
 * @brief Contains all internal methods and third party library calls
*/
namespace spic::internal // only used for doxgen generation
{
	
}
/**
 * @brief Contains internal timing classes
*/
namespace spic::internal::time
{
	/**
	 * @brief The internal static struct which keeps all timing related info
	*/
	struct InternalTime
	{
		/**
		 * @brief Converts clock_t to milliseconds
		 * @details units/(units/time) => time (seconds) * 1000 = milliseconds
		 * @param ticks An clock_t value
		 * @return The amount of miliseconds
		*/
		static constexpr double clockToMilliseconds(clock_t ticks) 
		{
			return (ticks / (double)CLOCKS_PER_SEC) * 1000.0;
		}

		/**
		 * @brief Start time of an begin frame
		*/
		static clock_t beginFrame;

		/**
		 * @brief Start time of an end frame
		*/
		static clock_t endFrame;

		/**
		 * @brief DeltaTime calculated by the EndFrame method
		*/
		static clock_t deltaTime;

		/**
		 * @brief Current amount of frames drawn in a second
		 * @details By 60 fps it can range from 0 to 59
		*/
		static unsigned int frames;

		/**
		 * @brief FrameRate counter.
		*/
		static double frameRate; 

		/**
		 * @brief The average frame time of a single frame.
		*/
		static double averageFrameTimeMilliseconds;

		/**
		 * @brief Sets the startValues of a new scene to 60 fps
		*/
		static void SetStartValues();
	
		/**
		 * @brief Sets the beginFrame timer.
		*/
		static void BeginFrame();

		/**
		 * @brief Sets the endTime timer.
		*/
		static void EndFrame();

		/**
		 * @brief Delays the current thread by structs deltaTime.
		 * @details Uses the std chrono lib
		*/
		static void Delay();

		/**
		 * @brief Getter
		 * @return Gets the current tick in miliseconds
		*/
		static double TickInMilliseconds();
	};
}
#endif