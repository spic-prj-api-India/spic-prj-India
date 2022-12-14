#ifndef PHYSICSEXTENSION_H_
#define PHYSICSEXTENSION_H_

#include <iostream>
#include <vector>
#include "IPhysicsExtension.hpp"
#include "Point.hpp"

namespace spic::extensions {
	class PhysicsExtensionImpl1;

	/**
	 * @brief A extension that handles standard physics 
	 */
	class PhysicsExtension1 : public IPhysicsExtension {
	public:
		PhysicsExtension1();
		~PhysicsExtension1();
		PhysicsExtension1(PhysicsExtension1&& rhs) noexcept;
		PhysicsExtension1& operator=(PhysicsExtension1&& rhs) noexcept;
		PhysicsExtension1(const PhysicsExtension1& rhs);
		PhysicsExtension1& operator=(const PhysicsExtension1& rhs);

		/**
		* @brief Resets all physic bodies
		* @spicapi
		*/
		void Reset(std::function<void(const std::shared_ptr<spic::GameObject>, const std::shared_ptr<spic::Collider>)> enterCallback,
			std::function<void(const std::shared_ptr<spic::GameObject>, const std::shared_ptr<spic::Collider>)> exitCallback,
			std::function<void(const std::shared_ptr<spic::GameObject>, const std::shared_ptr<spic::Collider>)> stayCallback) override;

		/**
		* @brief Add collision layer to physic world
		* @spicapi
		*/
		void AddCollisionLayer(const spic::TileLayer& collisionLayer) override;

		/**
		* @brief Add and updates physic bodies
		* @spicapi
		*/
		void Update(std::vector<std::shared_ptr<spic::GameObject>> entities) override;

		/**
		* @brief Registers collision listener
		* @spicapi
		*/
		void RegisterListener(ICollisionListener* listener) const override;

		/**
		* @brief Adds force to an entity with name
		* @spicapi
		*/
		void AddForce(const std::shared_ptr<GameObject>& entity, const spic::Point& forceDirection) override;

		/**
		* @brief Gets linear velocity of entity with name
		* @spicapi
		*/
		Point GetLinearVelocity(const std::string& entityName) override;

		/**
		* @brief Draw all colliders
		* @spicapi
		*/
		void DrawColliders() override;
	private:
        std::unique_ptr<PhysicsExtensionImpl1> physicsImpl;
	};
}

#endif // PHYSICSEXTENSION_H_