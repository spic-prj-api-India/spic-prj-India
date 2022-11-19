#ifndef PHYSICSEXTENSION_H_
#define PHYSICSEXTENSION_H_

#include <iostream>
#include <vector>
#include "GameObject.hpp"
#include "IPhysicsExtension.hpp"
#include "Point.hpp"

namespace spic::extensions {
	class PhysicsExtensionImpl;

	/**
	 * @brief A extension that handles standard physics 
	 */
	class PhysicsExtension : public IPhysicsExtension {
	public:
		explicit PhysicsExtension();
		~PhysicsExtension();
		PhysicsExtension(PhysicsExtension&& rhs) noexcept;
		PhysicsExtension& operator=(PhysicsExtension&& rhs) noexcept;
		PhysicsExtension(const PhysicsExtension& rhs);
		PhysicsExtension& operator=(const PhysicsExtension& rhs);

		/**
		* @brief Resets all physic bodies
		* @spicapi
		*/
		void Reset() override;

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
		* @brief Adds force to an entity
		* @spicapi
		*/
		void AddForce(std::shared_ptr<spic::GameObject> entity, const spic::Point& forceDirection) override;
	private:
        std::unique_ptr<PhysicsExtensionImpl> physicsImpl;
	};
}

#endif // PHYSICSEXTENSION_H_