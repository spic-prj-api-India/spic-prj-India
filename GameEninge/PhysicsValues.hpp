#ifndef PHYSICSVALUES_H_
#define PHYSICSVALUES_H_

#include "WindowValues.hpp"

namespace spic::extensions::PhysicsValues {
	/**
	 * @brief gravity used in physics world
	*/
	inline float GRAVITY = 9.81f;

	/**
	 * @brief Physics world uses meters instead of pixels. 
	 *		This variable can be changed to define the conversion from pixels to meters.
	 *		This will influence your physics world.
	*/
	inline float PIX2MET = 0.0023f;

	/**
	 * @brief Conversion from meters to pixels.
	*/
	inline const float MET2PIX = 1.0f / PIX2MET;

	/**
	 * @brief Width of physics world.
	*/
	inline const float SCALED_WIDTH = spic::window::WINDOW_WIDTH * PIX2MET;

	/**
	 * @brief Height of physics world.
	*/
	inline const float SCALED_HEIGHT = spic::window::WINDOW_HEIGHT * PIX2MET;
}

#endif // PHYSICSVALUES_H_