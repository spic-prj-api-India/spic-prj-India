#ifndef IPHYSICSEXTENSION_H_
#define IPHYSICSEXTENSION_H_

#include <vector>
#include <memory>
#include "IEngineExtension.hpp"
#include "ICollisionListener.hpp"

namespace extensions {
	/**
	 * @brief An interface for the physics extensions
	 */
	class IPhysicsExtension : public IEngineExtension {
	public:
		/**
		* @brief Resets all physics and removes entities from extension
		* @spicapi
		*/
		virtual void Reset() = 0;

		/**
		* @brief Add and updates entities with physics
		* @spicapi
		*/
		virtual void Update(std::vector<std::shared_ptr<spic::GameObject>> entities) = 0;

		/**
		* @brief Registers collision listener
		* @spicapi
		*/
		virtual void RegisterListener(ICollisionListener* listener) const = 0;

		/**
		* @brief Adds force to an entity
		* @spicapi
		*/
		virtual void AddForce(std::shared_ptr<spic::GameObject> entity, const spic::Point& forceDirection) = 0;
	};
}

#endif // IPHYSICSEXTENSION_H_