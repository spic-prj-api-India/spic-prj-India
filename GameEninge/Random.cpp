#include "Random.hpp"
#include <cstdlib>

namespace spic::internal::math {
	float RandomFloat()
	{
		return ((rand()) / (RAND_MAX + 1.0f));
	}

	float RandomClamped()
	{
		return RandomFloat() - RandomFloat();
	}
}