#ifndef BOX2DEXTENSION_H_
#define BOX2DEXTENSION_H_

#pragma warning(push, 0)
#include "box2d/box2d.h"
#pragma warning(pop)
#include <iostream>
#include <vector>
#include <map>
#include "GameObject.hpp"
#include "IEngineExtension.hpp"
#include "Point.hpp"
#include "RigidBody.hpp"
#include "Box2DCollisionListener.hpp"

namespace extensions {
	/**
	 * @brief A extension that handles physics with Box2D 
	 */
	class Box2DExtension : public extensions::IEngineExtension {
	public:
		Box2DExtension();
		
		/**
		* @brief Resets all physic bodies in world
		* @spicapi
		*/
		void Reset();
		/**
		* @brief Add and updates physic bodies in world
		* @spicapi
		*/
		void Update(std::vector<std::shared_ptr<spic::GameObject>> entities);

		/**
		* @brief Registers collision listener in world
		* @spicapi
		*/
		void RegisterListener(Box2DCollisionListener* listener) const;
		/**
		* @brief Adds force to an entity
		* @spicapi
		*/
		void AddForce(std::shared_ptr<spic::GameObject> entity, const spic::Point& forceDirection);
	private:
		void CreateEntity(const std::shared_ptr<spic::GameObject>& entity);
		b2Body* CreateBody(const std::shared_ptr<spic::GameObject>& entity, const std::shared_ptr<spic::RigidBody>& rigidBody);
		b2FixtureDef* CreateFixture(const std::shared_ptr<spic::GameObject>& entity, const std::shared_ptr<spic::RigidBody>& rigidBody) const;
		b2Shape* CreateShape(const std::shared_ptr<spic::GameObject>& entity) const;

		void UpdateEntity(const std::shared_ptr<spic::GameObject>& entity);
	private:
		std::unique_ptr<b2World> world;
		std::map<std::string, b2Body*> bodies;
		std::map<spic::BodyType, b2BodyType> bodyTypeConvertions;
	};
}

#endif // BOX2DEXTENSION_H_