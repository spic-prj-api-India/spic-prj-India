#ifndef BOX2DEXTENSION_H_
#define BOX2DEXTENSION_H_

// Use to remove box2d warnings from error list
#include <codeanalysis\warnings.h>
#pragma warning( push )
#pragma warning ( disable : ALL_CODE_ANALYSIS_WARNINGS )
#include "box2d/box2d.h"
#pragma warning( pop )
#include <iostream>
#include <vector>
#include <map>
#include "GameObject.hpp"
#include "IPhysicsExtension.hpp"
#include "Point.hpp"
#include "RigidBody.hpp"

namespace spic::extensions {
	/**
	 * @brief A extension that handles physics with Box2D 
	 */
	class Box2DExtension : public IPhysicsExtension {
	public:
		Box2DExtension();
		
		/**
		* @brief Resets all physic bodies in world
		* @spicapi
		*/
		void Reset() override;

		/**
		* @brief Add and updates physic bodies in world
		* @spicapi
		*/
		void Update(std::vector<std::shared_ptr<spic::GameObject>> entities) override;

		/**
		* @brief Registers collision listener in world
		* @spicapi
		*/
		void RegisterListener(ICollisionListener* listener) const override;

		/**
		* @brief Adds force to an entity
		* @spicapi
		*/
		void AddForce(std::shared_ptr<spic::GameObject> entity, const spic::Point& forceDirection) override;
	private:
		/**
		* @brief Creates body, fixture and shape and adds body to box2d world
		* @spicapi
		*/
		void CreateEntity(const std::shared_ptr<spic::GameObject>& entity);

		/**
		* @brief Creates box2d body with RigidBody of entity
		* @spicapi
		*/
		b2Body* CreateBody(const std::shared_ptr<spic::GameObject>& entity, const std::shared_ptr<spic::RigidBody>& rigidBody);

		/**
		* @brief Creates box2d fixture with RigidBody of entity
		* @spicapi
		*/
		b2FixtureDef* CreateFixture(const std::shared_ptr<spic::GameObject>& entity, const std::shared_ptr<spic::RigidBody>& rigidBody) const;

		/**
		* @brief Creates box2d shape with Colliders of entity
		* @spicapi
		*/
		b2Shape* CreateShape(const std::shared_ptr<spic::GameObject>& entity) const;

		/**
		* @brief Updates position and rotation for box2d body if transform of entity has 
		*		been changed outside extension
		* @spicapi
		*/
		void UpdateEntity(const std::shared_ptr<spic::GameObject>& entity);
	private:
		std::unique_ptr<b2World> world;
		std::map<std::string, b2Body*> bodies;
		std::map<spic::BodyType, b2BodyType> bodyTypeConvertions;
	};
}

#endif // BOX2DEXTENSION_H_