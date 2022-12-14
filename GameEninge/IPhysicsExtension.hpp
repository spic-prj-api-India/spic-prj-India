#ifndef IPHYSICSEXTENSION_H_
#define IPHYSICSEXTENSION_H_

#include <vector>
#include <memory>
#include "IEngineExtension.hpp"
#include "ICollisionListener.hpp"

namespace spic::extensions{
	/**
	 * @brief An interface for the physics extensions
	 */
	class IPhysicsExtension : public spic::extensions::IEngineExtension{
	public:
		IPhysicsExtension();
		~IPhysicsExtension();
		IPhysicsExtension(IPhysicsExtension&& rhs) noexcept;
		IPhysicsExtension& operator=(IPhysicsExtension&& rhs) noexcept;
		IPhysicsExtension(const IPhysicsExtension& rhs);
		IPhysicsExtension& operator=(const IPhysicsExtension& rhs);

		/**
		* @brief Resets all physics and removes entities from extension
		* @spicapi
		*/
		virtual void Reset(std::function<void(const std::shared_ptr<spic::GameObject>, const std::shared_ptr<spic::Collider>)> enterCallback,
			std::function<void(const std::shared_ptr<spic::GameObject>, const std::shared_ptr<spic::Collider>)> exitCallback,
			std::function<void(const std::shared_ptr<spic::GameObject>, const std::shared_ptr<spic::Collider>)> stayCallback) = 0;

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