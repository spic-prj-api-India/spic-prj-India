#pragma once
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

namespace extensions {
	class Box2DExtension : public extensions::IEngineExtension {
	public:
		Box2DExtension();
		void Reset();
		void Update(std::vector<std::shared_ptr<spic::GameObject>> entities);
		void RegisterListener(std::unique_ptr<b2ContactListener> listener);
		void AddForce(std::shared_ptr<spic::GameObject> entity, const spic::Point& forceDirection);
	private:
		void CreateEntity(const std::shared_ptr<spic::GameObject>& entity);
		b2Body* CreateBody(const std::shared_ptr<spic::GameObject>& entity, const std::shared_ptr<spic::RigidBody>& rigidBody);
		b2FixtureDef* CreateFixture(const std::shared_ptr<spic::GameObject>& entity, const std::shared_ptr<spic::RigidBody>& rigidBody);
		b2Shape* CreateShape(const std::shared_ptr<spic::GameObject>& entity);
		void UpdateEntity(const std::shared_ptr<spic::GameObject>& entity);
	private:
		std::unique_ptr<b2World> world;
		std::map<std::string, b2Body*> bodies;
		std::map<spic::BodyType, b2BodyType> bodyTypeConvertions;
	};
}