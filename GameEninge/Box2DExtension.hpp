#pragma once
#include <box2d.h>
#include <iostream>
#include <vector>
#include <map>
#include "GameObject.hpp"
#include "IEngineExtension.hpp"
#include "Point.hpp"
#include "RigidBody.hpp"

namespace extensions {
	class Box2DExtension : public IEngineExtension {
	public:
		Box2DExtension();
		void Reset();
		void Update(std::vector<std::shared_ptr<spic::GameObject>> entities);
		void AddForce(std::shared_ptr<spic::GameObject> entity, const spic::Point& forceDirection);
	private:
		void CreateEntity(const std::shared_ptr<spic::GameObject>& entity);
		b2Body* CreateBody(const std::shared_ptr<spic::GameObject>& entity);
		b2FixtureDef* CreateFixture(const std::shared_ptr<spic::GameObject>& entity);
		b2Shape* CreateShape(const std::shared_ptr<spic::GameObject>& entity);
		void UpdateEntity(const std::shared_ptr<spic::GameObject>& entity);
	private:
		std::unique_ptr<b2World> world;
		std::map<std::string, b2Body*> bodies;
		std::map<spic::BodyType, b2BodyType> bodyTypeConvertions;
	};
}