#ifndef IPHYSICSEXTENSION_H_
#define IPHYSICSEXTENSION_H_

#include <vector>
#include <memory>
#include "IEngineExtension.hpp"
#include "ICollisionListener.hpp"
#include "TileLayer.hpp"

namespace spic::extensions{
	typedef std::function<void(const std::shared_ptr<spic::GameObject>&, const std::shared_ptr<spic::Collider>&)> CollisionCallback;

	/**
	 * @brief An interface for the physics extensions
	 */
	class IPhysicsExtension : public spic::extensions::IEngineExtension{
	public:
		IPhysicsExtension();
		virtual ~IPhysicsExtension() = default;
		IPhysicsExtension(IPhysicsExtension&& rhs) = default;
		virtual IPhysicsExtension& operator=(IPhysicsExtension&& rhs) = default;
		IPhysicsExtension(const IPhysicsExtension& rhs) = default;
		virtual IPhysicsExtension& operator=(const IPhysicsExtension& rhs) = default;

		/**
		 * @brief Resets all physics and removes entities from extension
		 * @param enterCallback Callback that runs OnTriggerEnter2D in behaviour scripts of entity 
		 * @param exitCallback Callback that runs OnTriggerExit2D in behaviour scripts of entity 
		 * @param stayCallback  Callback that runs OnTriggerStay2D in behaviour scripts of entity 
		*/
		virtual void Reset(
			CollisionCallback enterCallback,
			CollisionCallback exitCallback,
			CollisionCallback stayCallback) = 0;

		/**
		 * @brief Add collision layer to physic world
		 * @param collisionLayer Tiled layer that is used for collision
		*/
		virtual void AddCollisionLayer(const spic::tiled::TileLayer& collisionLayer) = 0;

		/**
		 * @brief Add and updates entities with physics
		 * @param entities Entities to update
		*/
		virtual void Update(std::vector<std::shared_ptr<spic::GameObject>>& entities) = 0;

		/**
		 * @brief Adds force to an entity
		 * @param entity Entity were force will be added to
		 * @param forceDirection Force that will be applied
		*/
		virtual void AddForce(const std::shared_ptr<GameObject>& entity, const spic::Point& forceDirection) = 0;

		/**
		 * @brief Removes entity from physics
		 * @param entityName Name of entity that will be removed
		*/
		virtual void RemoveEntity(const std::string& entityName) = 0;

		/**
		 * @brief Gets linear velocity of entity with name
		 * @param entityName Name of entity that will be removed
		 * @return Point Returns Linear velocity
		*/
		virtual Point GetLinearVelocity(const std::string& entityName) = 0;

		/**
		 * @brief Draw all colliders
		*/
		virtual void DrawColliders() = 0;

		/**
		 * @brief Amount of times other systems should run
		 * @return int 
		*/
		virtual int RunTimes() = 0;

		/**
		 * @brief Clears all current forces
		*/
		virtual void ClearForces() = 0;
	};
}

#endif // IPHYSICSEXTENSION_H_