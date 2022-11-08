#include <regex>
#include <memory>
#include <mutex>
#include "Box2DExtension.hpp"
#include "CircleCollider.hpp"
#include "BoxCollider.hpp"

namespace extensions {
	inline float GRAVITY = 9.81f;

	Box2DExtension::Box2DExtension() {
		bodyTypeConvertions = {
			{spic::BodyType::staticBody, b2_staticBody},
			{spic::BodyType::kinematicBody, b2_kinematicBody},
			{spic::BodyType::dynamicBody, b2_dynamicBody},
		};
		world = nullptr;
		Reset();
	}

	void Box2DExtension::Reset() {
		world = std::make_unique<b2World>(b2Vec2(0.0f, GRAVITY));
		bodies = std::map<std::string, b2Body*>();
	}

	void Box2DExtension::Update(std::vector<std::shared_ptr<spic::GameObject>> entities) {
		// Update or create entity bodiese
		for (auto& entity : entities) {
			bool exists = bodies.find(entity->GetTag()) != bodies.end();
			if (exists)
				UpdateEntity(entity);
			else
				CreateEntity(entity);

		}
		// Update world
		world->Step(1.0f / 60.0f, int32(6), int32(2.0));
		// Update entities
		for (auto& entity : entities) {
			// Get body
			b2Body* body = bodies[entity->GetTag()];

			// Get transform
			b2Vec2 position = body->GetPosition();
			float rotation = body->GetAngle();

			// Update entity
			entity->GetTranform()->position.x = position.x;
			entity->GetTranform()->position.y = position.y;
			entity->GetTranform()->rotation = rotation;
		}
	}

	void Box2DExtension::CreateEntity(const std::shared_ptr<spic::GameObject>& entity) {
		// Create body
		b2Body* body = CreateBody(entity);

		// Set velocity
		b2Vec2 velocity;
		velocity.Set(0, entity->GetRigidBody()->GetGravityScale());
		body->SetLinearVelocity(velocity);

		// Create fixture
		b2FixtureDef* fixtureDef = CreateFixture(entity);
		body->CreateFixture(fixtureDef);

		// Add to bodies
		bodies[entity->GetTag()] = body;
	}

	b2Body* Box2DExtension::CreateBody(const std::shared_ptr<spic::GameObject>& entity) {
		// cartesian origin
		float ground_x = entity->GetTranform()->position.x;
		float ground_y = entity->GetTranform()->position.y;

		b2BodyDef bodyDef;
		bodyDef.type = bodyTypeConvertions[entity->GetRigidBody()->GetBodyType()];
		bodyDef.position.Set(ground_x, ground_y); // set the starting position x and y cartesian
		bodyDef.angle = entity->GetTranform()->rotation;

		b2Body* body = world->CreateBody(&bodyDef);
		return body;
	}

	b2FixtureDef* Box2DExtension::CreateFixture(const std::shared_ptr<spic::GameObject>& entity) {
		b2FixtureDef* fixtureDef = new b2FixtureDef();
		fixtureDef->shape = CreateShape(entity);
		fixtureDef->density = entity->GetRigidBody()->GetMass();
		fixtureDef->friction = 0.3f;
		fixtureDef->restitution = 0.5f;
		return fixtureDef;
	}

	b2Shape* Box2DExtension::CreateShape(const std::shared_ptr<spic::GameObject>& entity) {
		if (entity->GetCollider<spic::Collider>() == nullptr)
			return nullptr;
		spic::BoxCollider* boxCollider = entity->GetCollider<spic::BoxCollider>();
		if (boxCollider != nullptr) {
			b2PolygonShape* boxShape = new b2PolygonShape();
			boxShape->SetAsBox((boxCollider->Width() / 2.0f) - boxShape->m_radius, (boxCollider->Height() / 2.0f) - boxShape->m_radius); // will be 0.5 x 0.5
			return boxShape;
		}
		spic::CircleCollider* circleCollider = entity->GetCollider<spic::CircleCollider>();
		if (circleCollider != nullptr) {

		}
		return nullptr;
	}

	void Box2DExtension::UpdateEntity(const std::shared_ptr<spic::GameObject>& entity) {
		// Get body
		b2Body* body = bodies[entity->GetTag()];

		// Get Box2D transform
		b2Vec2 b2Position = body->GetPosition();
		float b2Rotation = body->GetAngle();

		// Get entity transform
		spic::Point ePosition = entity->GetTranform()->position;
		float eRotation = entity->GetTranform()->rotation;

		// Update
		bool updated = false;
		if (b2Position.x != ePosition.x) {
			b2Position.x = ePosition.x;
			updated = true;
		}
		if (b2Position.y != ePosition.y) {
			b2Position.y = ePosition.y;
			updated = true;
		}
		if (b2Rotation != eRotation) {
			b2Rotation = eRotation;
			updated = true;
		}
		if (updated) {
			body->SetTransform(b2Position, b2Rotation);
			b2Vec2 velocity;
			velocity.Set(0, entity->GetRigidBody()->GetGravityScale());
			body->SetLinearVelocity(velocity);
		}
	}

	void Box2DExtension::AddForce(std::shared_ptr<spic::GameObject> entity, const spic::Point& forceDirection) {
		b2Body* body = bodies[entity->GetTag()];

		b2Vec2 velocity;
		velocity.Set(forceDirection.x, forceDirection.y);
		body->SetLinearVelocity(velocity);
	}
}