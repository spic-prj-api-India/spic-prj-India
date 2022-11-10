#include <regex>
#include <memory>
#include <mutex>
#include "Box2DExtension.hpp"
#include "CircleCollider.hpp"
#include "BoxCollider.hpp"

namespace extensions {
	inline float GRAVITY = 9.81f;

	Box2DExtension::Box2DExtension() : IEngineExtension() {
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
			bool exists = bodies.find(entity->Tag()) != bodies.end();
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
			b2Body* body = bodies[entity->Tag()];

			// Get transform
			b2Vec2 position = body->GetPosition();
			float rotation = body->GetAngle();

			// Update entity
			entity->Transform()->position.x = position.x;
			entity->Transform()->position.y = position.y;
			entity->Transform()->rotation = rotation;
		}
	}

	void Box2DExtension::CreateEntity(const std::shared_ptr<spic::GameObject>& entity) {
		// Create body
		std::shared_ptr<spic::RigidBody> rigidBody = entity->GetComponent<spic::RigidBody>();
		b2Body* body = CreateBody(entity, rigidBody);

		// Set velocity
		b2Vec2 velocity;
		velocity.Set(0, rigidBody->GetGravityScale());
		body->SetLinearVelocity(velocity);

		// Create fixture
		b2FixtureDef* fixtureDef = CreateFixture(entity, rigidBody);
		body->CreateFixture(fixtureDef);

		// Add to bodies
		bodies[entity->Tag()] = body;
	}

	b2Body* Box2DExtension::CreateBody(const std::shared_ptr<spic::GameObject>& entity, const std::shared_ptr<spic::RigidBody>& rigidBody) {
		// cartesian origin
		float ground_x = entity->Transform()->position.x;
		float ground_y = entity->Transform()->position.y;

		b2BodyDef bodyDef;
		bodyDef.type = bodyTypeConvertions[rigidBody->GetBodyType()];
		bodyDef.position.Set(ground_x, ground_y); // set the starting position x and y cartesian
		bodyDef.angle = entity->Transform()->rotation;

		b2Body* body = world->CreateBody(&bodyDef);
		return body;
	}

	b2FixtureDef* Box2DExtension::CreateFixture(const std::shared_ptr<spic::GameObject>& entity, const std::shared_ptr<spic::RigidBody>& rigidBody) {
		b2FixtureDef* fixtureDef = new b2FixtureDef();
		fixtureDef->shape = CreateShape(entity);
		fixtureDef->density = rigidBody->GetMass();
		fixtureDef->friction = 0.3f;
		fixtureDef->restitution = 0.5f;
		return fixtureDef;
	}

	b2Shape* Box2DExtension::CreateShape(const std::shared_ptr<spic::GameObject>& entity) {
		if (!entity->HasComponent<spic::Collider>())
			return nullptr;
		std::shared_ptr<spic::BoxCollider> boxCollider = entity->GetComponent<spic::BoxCollider>();
		if (boxCollider != nullptr) {
			b2PolygonShape* boxShape = new b2PolygonShape();
			boxShape->SetAsBox((boxCollider->Width() / 2.0f) - boxShape->m_radius, (boxCollider->Height() / 2.0f) - boxShape->m_radius); // will be 0.5 x 0.5
			return boxShape;
		}
		std::shared_ptr<spic::CircleCollider> circleCollider = entity->GetComponent<spic::CircleCollider>();
		if (circleCollider != nullptr) {
			b2CircleShape* circleShape = new b2CircleShape();
			circleShape->m_radius = circleCollider->Radius();
		}
		return nullptr;
	}

	void Box2DExtension::UpdateEntity(const std::shared_ptr<spic::GameObject>& entity) {
		// Get body
		std::shared_ptr<spic::RigidBody> rigidBody = entity->GetComponent<spic::RigidBody>();
		b2Body* body = bodies[entity->Tag()];

		// Get Box2D transform
		b2Vec2 b2Position = body->GetPosition();
		float b2Rotation = body->GetAngle();

		// Get entity transform
		spic::Point ePosition = entity->Transform()->position;
		float eRotation = entity->Transform()->rotation;

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
			velocity.Set(0, rigidBody->GetGravityScale());
			body->SetLinearVelocity(velocity);
		}
	}

	void Box2DExtension::AddForce(std::shared_ptr<spic::GameObject> entity, const spic::Point& forceDirection) {
		b2Body* body = bodies[entity->Tag()];

		b2Vec2 velocity;
		velocity.Set(forceDirection.x, forceDirection.y);
		body->SetLinearVelocity(velocity);
	}
}