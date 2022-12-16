#ifndef RANDOM_H_
#define RANDOM_H_

#include <limits>

namespace spic::internal::math 
{
	constexpr float MaxFloat = (std::numeric_limits<float>::max)();

	/**
	 * @brief Returns a random float between zero and 1
	*/
	float RandomFloat();

	/**
	 * @brief Returns a random float in the range -1 < n < 1
	*/
	float ClampedRandomFloat();
}

#endif // RANDOM_H_
