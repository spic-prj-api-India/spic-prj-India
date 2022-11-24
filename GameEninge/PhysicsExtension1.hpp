#ifndef PHYSICSEXTENSION_H_
#define PHYSICSEXTENSION_H_

#include <iostream>
#include <vector>
#include "GameObject.hpp"
#include "IPhysicsExtension.hpp"
#include "Point.hpp"

namespace spic::extensions {
	class PhysicsExtensionImpl1;

	/**
	 * @brief A extension that handles standard physics 
	 */
	class PhysicsExtension1 : public IPhysicsExtension {
	public:
		explicit PhysicsExtension1();
		~PhysicsExtension1();
		PhysicsExtension1(PhysicsExtension1&& rhs) noexcept;
		PhysicsExtension1& operator=(PhysicsExtension1&& rhs) noexcept;
		PhysicsExtension1(const PhysicsExtension1& rhs);
		PhysicsExtension1& operator=(const PhysicsExtension1& rhs);

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
        std::unique_ptr<PhysicsExtensionImpl1> physicsImpl;
	};
}

#endif // PHYSICSEXTENSION_H_