#include <regex>
#include <memory>
#include <mutex>
#include <map>
// Use to remove box2d warnings from error list
#pragma warning(push, 0)
#include "box2d/box2d.h"
#pragma warning(pop)
#include "PhysicsExtension.hpp"
#include "CircleCollider.hpp"
#include "BoxCollider.hpp"
#include "ICollisionListener.hpp"
#include "Box2DCollisionListener.hpp"
#include "PhysicsInfo.hpp"

namespace spic::extensions {
	std::unique_ptr<b2World> world;
	std::map<std::string, b2Body*> bodies;
	std::map<spic::BodyType, b2BodyType> bodyTypeConvertions;

	class PhysicsExtensionImpl {
	public:
		PhysicsExtensionImpl()
		{
			world = nullptr;
			bodyTypeConvertions = {
				{spic::BodyType::staticBody, b2_staticBody},
				{spic::BodyType::kinematicBody, b2_kinematicBody},
				{spic::BodyType::dynamicBody, b2_dynamicBody},
			};
			Reset();
		}

		~PhysicsExtensionImpl() = default;

		/**
		* @brief Resets all physic bodies in world
		* @spicapi
		*/
		void Reset()
		{
			world = std::make_unique<b2World>(b2Vec2(0.0f, spic::internal::extensions::GRAVITY));
		}

		/**
		* @brief Add and updates physic bodies in world
		* @spicapi
		*/
		void Update(std::vector<std::shared_ptr<spic::GameObject>> entities)
		{
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
				const b2Vec2 position = body->GetPosition();
				const float rotation = body->GetAngle();

				// Update entity
				entity->Transform()->position.x = position.x;
				entity->Transform()->position.y = position.y;
				entity->Transform()->rotation = rotation;
			}
		}

		/**
		* @brief Registers collision listener in world
		* @spicapi
		*/
		void RegisterListener(spic::extensions::ICollisionListener* listener) const
		{
			b2ContactListener* box2DListener = dynamic_cast<spic::internal::extensions::Box2DCollisionListener*>(listener);
			world->SetContactListener(box2DListener);
		}

		/**
		* @brief Adds force to an entity
		* @spicapi
		*/
		void AddForce(std::shared_ptr<spic::GameObject> entity, const spic::Point& forceDirection)
		{
			b2Body* body = bodies[entity->Tag()];

			b2Vec2 velocity;
			velocity.Set(forceDirection.x, forceDirection.y);
			body->SetLinearVelocity(velocity);
		}
	private:
		/**
		* @brief Creates body, fixture and shape and adds body to box2d world
		* @spicapi
		*/
		void CreateEntity(const std::shared_ptr<spic::GameObject>& entity)
		{
			// Create body
			std::shared_ptr<spic::RigidBody> rigidBody = entity->GetComponent<spic::RigidBody>();
			b2Body* body = CreateBody(entity, rigidBody);

			// Set velocity
			b2Vec2 velocity;
			velocity.Set(0, rigidBody->GravityScale());
			body->SetLinearVelocity(velocity);

			// Create fixture
			if (entity->HasComponent<spic::Collider>()) {
				const std::unique_ptr<b2FixtureDef> fixtureDef = CreateFixture(entity, rigidBody);
				body->CreateFixture(fixtureDef.get());

				// Set data
				body->GetUserData().pointer = reinterpret_cast<uintptr_t>(entity.get());
			}

			// Add to bodies
			bodies[entity->Tag()] = body;
		}

		/**
		* @brief Creates box2d body with RigidBody of entity
		* @spicapi
		*/
		b2Body* CreateBody(const std::shared_ptr<spic::GameObject>& entity, const std::shared_ptr<spic::RigidBody>& rigidBody)
		{
			// cartesian origin
			const float ground_x = entity->Transform()->position.x;
			const float ground_y = entity->Transform()->position.y;

			b2BodyDef bodyDef;
			bodyDef.type = bodyTypeConvertions[rigidBody->BodyType()];
			bodyDef.position.Set(ground_x, ground_y); // set the starting position x and y cartesian
			bodyDef.angle = entity->Transform()->rotation;
			bodyDef.gravityScale = rigidBody->GravityScale();

			b2Body* body = world->CreateBody(&bodyDef);
			return body;
		}

		/**
		* @brief Creates box2d fixture with RigidBody of entity
		* @spicapi
		*/
		std::unique_ptr<b2FixtureDef> CreateFixture(const std::shared_ptr<spic::GameObject>& entity, const std::shared_ptr<spic::RigidBody>& rigidBody) const
		{
			std::unique_ptr<b2FixtureDef> fixtureDef = std::make_unique<b2FixtureDef>();
			const b2Shape* shape = CreateShape(entity);
			if (shape != nullptr)
				fixtureDef->shape = shape;
			fixtureDef->density = rigidBody->Mass();
			fixtureDef->friction = 0.3f;
			fixtureDef->restitution = 0.5f;
			return std::move(fixtureDef);
		}

		/**
		* @brief Creates box2d shape with Colliders of entity
		* @spicapi
		*/
		b2Shape* CreateShape(const std::shared_ptr<spic::GameObject>& entity) const
		{
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
				return circleShape;
			}
			return nullptr;
		}

		/**
		* @brief Updates position and rotation for box2d body if transform of entity has
		*		been changed outside extension
		* @spicapi
		*/
		void UpdateEntity(const std::shared_ptr<spic::GameObject>& entity)
		{
			// Get body
			std::shared_ptr<spic::RigidBody> rigidBody = entity->GetComponent<spic::RigidBody>();
			b2Body* body = bodies[entity->Tag()];

			// Get Box2D transform
			b2Vec2 b2Position = body->GetPosition();
			float b2Rotation = body->GetAngle();

			// Get entity transform
			const spic::Point ePosition = entity->Transform()->position;
			const float eRotation = entity->Transform()->rotation;

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
				velocity.Set(0, rigidBody->GravityScale());
				body->SetLinearVelocity(velocity);
			}
		}
	};

	PhysicsExtension::PhysicsExtension() : physicsImpl(new PhysicsExtensionImpl())
	{}

	PhysicsExtension::~PhysicsExtension() = default;

	PhysicsExtension::PhysicsExtension(PhysicsExtension&&) noexcept = default;

	PhysicsExtension& PhysicsExtension::operator=(PhysicsExtension&&) noexcept = default;

	PhysicsExtension::PhysicsExtension(const PhysicsExtension& rhs)
		: physicsImpl(new PhysicsExtensionImpl(*rhs.physicsImpl))
	{}

	PhysicsExtension& PhysicsExtension::operator=(const PhysicsExtension& rhs) 
	{
		if (this != &rhs)
			physicsImpl.reset(new PhysicsExtensionImpl(*rhs.physicsImpl));
		return *this;
	}

	void spic::extensions::PhysicsExtension::Reset()
	{
		physicsImpl->Reset();
	}

	void spic::extensions::PhysicsExtension::Update(std::vector<std::shared_ptr<spic::GameObject>> entities)
	{
		physicsImpl->Update(entities);
	}

	void spic::extensions::PhysicsExtension::RegisterListener(ICollisionListener* listener) const
	{
		physicsImpl->RegisterListener(listener);
	}

	void spic::extensions::PhysicsExtension::AddForce(std::shared_ptr<spic::GameObject> entity, const spic::Point& forceDirection)
	{
		physicsImpl->AddForce(entity, forceDirection);
	}
}