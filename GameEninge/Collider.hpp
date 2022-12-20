#ifndef COLLIDER2D_H_
#define COLLIDER2D_H_

#include "Component.hpp"

namespace spic {
	/**
	 * @brief The base class for all colliders.
	 * @spicapi
	 */
	class Collider : public Component {
	public:
		/**
		 * @brief Default constructor
		 *          friction, bounciness set to zero
		 *          enabled set to true
		*/
		Collider();

		/**
		 * @brief Constructor
		 * @param friction The desired friction
		 * @param bounciness The desired bounciness
		 * @param enabled Enable or disables collider
		 * @throws Throws if bounciness is not between 0 or 1
		*/
		Collider(const float friction, const float bounciness, const bool enabled = true);

		/**
		 * @return The collider width and height
		 *              point.x is width, point.y is height
		 * @sharedapi
		*/
		virtual Point Size() const = 0;

		/**
	     * @brief Get the collider's bounciness
	     * @details For more information look at property documentation
	     * @return The bounciness
	     * @sharedapi
	    */
		float Bounciness() const;

		/**
		 * @brief Set the collider's bounciness
		 * @param newBounciness The desired bounciness
		 * @throws Throws if newBounciness is not between 0 or 1
		 * @sharedapi
		*/
		void Bounciness(const float newBounciness);

		/**
		 * @brief Get the collider's friction
		 * @return The friction
		 * @sharedapi
		*/
		float Friction() const;

		/**
		 * @brief Set the collider's friction
		 * @param newFriction The desired friction
		 * @sharedapi
		*/
		void Friction(const float newFriction);

		/**
		 * @brief Is collision detection enabled
		 * @return The current enabled
		 * @sharedapi
		*/
		bool Enabled() const;

		/**
		 * @brief Disables collision detection
		 * @sharedapi
		*/
		void Disable();

		/**
		 * @brief Enables collision detection
		 * @sharedapi
		*/
		void Enable();
	private:
		/**
		 * @brief How bouncy is the surface? A value of 0 will not bounce. A value of 1 will bounce without any loss of energy.
		*/
		float bounciness;

		/**
		 * @brief The friction used when already moving. This value is usually between 0 and 1.
		*/
		float friction;

		/**
		 * @brief Variable sets if collision detection is enabled.
		*/
		bool enabled;
	};
}

#endif // COLLIDER2D_H_
