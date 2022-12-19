#include "Obstacle.hpp"

namespace spic {
	Obstacle::Obstacle(const float boundingRadius) : boundingRadius{ boundingRadius }
	{
	}

	float Obstacle::BRadius() const
	{
		return this->boundingRadius;
	}
}