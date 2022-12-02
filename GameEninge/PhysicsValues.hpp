#ifndef PHYSICSVALUES_H_
#define PHYSICSVALUES_H_

namespace spic::extensions::PhysicsValues {
	/**
	 * @brief gravity used in physics world
	*/
	inline float GRAVITY = 9.81f;

	/**
	 * @brief Scaling factor in world.
	 *      if game object is 100x100 pixels and scaling factor 0.01f
	 *      then game object is 1x1 in meters
	*/
	inline float SCALING_FACTOR = 0.01f;
}

#endif // PHYSICSVALUES_H_