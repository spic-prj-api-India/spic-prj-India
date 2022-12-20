#ifndef PHYSICSEXTENSION_H_
#define PHYSICSEXTENSION_H_

#include <iostream>
#include <vector>
#include "IPhysicsExtension.hpp"
#include "Point.hpp"

namespace spic::extensions 
{
	/**
	 * @brief Contains the box2d implementation
	*/
	class PhysicsExtensionImpl1;

	/**
	 * @brief A extension that handles standard physics 
	*/
	class PhysicsExtension1 : public IPhysicsExtension {
	public:
		PhysicsExtension1(const float pix2Met, const int velocityIterations = 8, const int positionIterations = 3, const float stableUpdateFrameRate = 1.0f / 60.0f);
		~PhysicsExtension1();
		PhysicsExtension1(PhysicsExtension1&& rhs) noexcept;
		PhysicsExtension1& operator=(PhysicsExtension1&& rhs) noexcept;
		PhysicsExtension1(const PhysicsExtension1& rhs);
		PhysicsExtension1& operator=(const PhysicsExtension1& rhs);

		/**
		 * @brief Resets all physic bodies
		 * @param enterCallback Callback that runs OnTriggerEnter2D in behaviour scripts of entity
		 * @param exitCallback Callback that runs OnTriggerExit2D in behaviour scripts of entity
		 * @param stayCallback  Callback that runs OnTriggerStay2D in behaviour scripts of entity
		*/
		void Reset(std::function<void(const std::shared_ptr<spic::GameObject>&, const std::shared_ptr<spic::Collider>&)> enterCallback,
			std::function<void(const std::shared_ptr<spic::GameObject>&, const std::shared_ptr<spic::Collider>&)> exitCallback,
			std::function<void(const std::shared_ptr<spic::GameObject>&, const std::shared_ptr<spic::Collider>&)> stayCallback) override;

		/**
		 * @brief Add collision layer to physic world
		 * @param collisionLayer Tiled layer that is used for collision
		*/
		void AddCollisionLayer(const spic::tiled::TileLayer& collisionLayer) override;

		/**
		 * @brief Add and updates entities with physics
		 * @param entities Entities to update
		*/
		void Update(std::vector<std::shared_ptr<spic::GameObject>>& entities) override;

		/**
		 * @brief Adds force to an entity
		 * @param entity Entity were force will be added to
		 * @param forceDirection Force that will be applied
		*/
		void AddForce(const std::shared_ptr<GameObject>& entity, const spic::Point& forceDirection) override;

		/**
		 * @brief Removes entity from physics
		 * @param name Name of entity that will be removed
		*/
		void RemoveEntity(const std::string& name) override;

		/**
		 * @brief Gets linear velocity of entity with name
		 * @return Point Returns Linear velocity
		*/
		Point GetLinearVelocity(const std::string& entityName) override;

		/**
		 * @brief Draw all colliders
		*/
		void DrawColliders() override;

		/**
		 * @brief Amount of times other systems should run
		 * @return int
		*/
		int RunTimes() override;
	private:
        std::unique_ptr<PhysicsExtensionImpl1> physicsImpl;
	};
}

#endif // PHYSICSEXTENSION_H_