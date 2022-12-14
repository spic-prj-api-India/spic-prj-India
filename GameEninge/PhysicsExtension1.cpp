#include <regex>
#include <memory>
#include <mutex>
#include <map>
// Use to remove box2d warnings from error list
#include <codeanalysis\warnings.h>
#pragma warning( push )
#pragma warning ( disable : ALL_CODE_ANALYSIS_WARNINGS )
#include "box2d/box2d.h"
#pragma warning( pop )
#include "PhysicsExtension1.hpp"
#include "CircleCollider.hpp"
#include "BoxCollider.hpp"
#include "ICollisionListener.hpp"
#include "Box2DCollisionListener.hpp"
#include "PhysicsValues.hpp"
#include "RigidBody.hpp"
#include "ForceDriven.hpp"
#include "Defaults.hpp"
#include "TileLayer.hpp"
#include "Renderer.hpp"

namespace spic::extensions {
	std::unique_ptr<b2World> world;
	std::map<std::string, b2Body*> bodies;
	std::map<spic::BodyType, b2BodyType> bodyTypeConvertions;

	class PhysicsExtensionImpl1 {
	public:
		PhysicsExtensionImpl1()
		{
			world = nullptr;
			bodyTypeConvertions = {
				{spic::BodyType::staticBody, b2_staticBody},
				{spic::BodyType::kinematicBody, b2_kinematicBody},
				{spic::BodyType::dynamicBody, b2_dynamicBody},
			};
			Reset();
		}

		~PhysicsExtensionImpl1() = default;

		/**
		* @brief Resets all physic bodies in world
		* @spicapi
		*/
		void Reset()
		{
			world = std::make_unique<b2World>(b2Vec2(0.0f, PhysicsValues::GRAVITY));
		}

		/**
		* @brief Add collision layer in world
		* @spicapi
		*/
		void AddCollisionLayer(const spic::TileLayer& collisionLayer) {
			const float tileSize = static_cast<float>(collisionLayer.GetTilesize());
			Matrix matrix = collisionLayer.GetMatrix();
			const Point size = collisionLayer.GetSize();
			for (int rowIndex = 0; rowIndex < size.y; rowIndex++)
			{
				for (int colIndex = 0; colIndex < size.x; colIndex++)
				{
					const bool tileExists = matrix[colIndex][rowIndex] != 0;
					if (!tileExists) continue;

					const float x = static_cast<float>(colIndex * tileSize);
					const float y = static_cast<float>(rowIndex * tileSize);
					const Point origin = { x,  y };
					AddEdges(matrix, colIndex, rowIndex, origin, tileSize);
				}
			}
		}

		/**
		* @brief Add and updates physic bodies in world
		* @spicapi
		*/
		void Update(std::vector<std::shared_ptr<spic::GameObject>> entities)
		{
			// Update or create entity bodiese
			for (auto& entity : entities) {
				bool exists = bodies.find(entity->Name()) != bodies.end();
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
				b2Body* body = bodies[entity->Name()];

				// Get transform
				const b2Vec2 position = body->GetPosition();
				const float rotation = body->GetAngle();

				// Update entity
				entity->Transform()->position.x = position.x / PhysicsValues::SCALING_FACTOR;
				entity->Transform()->position.y = position.y / PhysicsValues::SCALING_FACTOR;
				if (!spic::TypeHelper::SharedPtrIsOfType<ForceDriven>(entity))
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
		void AddForce(const std::shared_ptr<GameObject>& entity, const spic::Point& forceDirection)
		{
			const std::string& name = entity->Name();
			if (bodies.count(name) == 0)
				CreateEntity(entity);
			b2Body* body = bodies[name];
			b2Vec2 force = { forceDirection.x, forceDirection.y };

			body->ApplyForce(force, body->GetWorldCenter(), true);
		}

		/**
		* @brief Gets linear velocty of entity
		* @spicapi
		*/
		Point GetLinearVelocity(const std::string& name) {
			if (bodies.count(name) == 0)
				return { 0.0f, 0.0f };
			const b2Vec2 linearVelocity = bodies[name]->GetLinearVelocity();
			return { linearVelocity.x, linearVelocity.y };
		}

		/**
		* @brief Draw all colliders in world
		* @spicapi
		*/
		void DrawColliders()
		{
			const b2Body* currentBody = world->GetBodyList();
			while (currentBody != nullptr)
			{
				const b2Shape* shape = currentBody->GetFixtureList()->GetShape();
				if (shape == nullptr) {
					currentBody = currentBody->GetNext();
					continue;
				}
				switch (shape->GetType()) {
				case b2Shape::e_polygon:
					DrawBoxCollider(*currentBody, static_cast<const b2PolygonShape&>(*shape));
					break;
				case b2Shape::e_edge:
					DrawEdgeCollider(static_cast<const b2EdgeShape&>(*shape));
					break;
				}
				currentBody = currentBody->GetNext();
			}
		}
	private:
		void AddEdges(const Matrix& matrix, const int colIndex, const int rowIndex, const Point& origin, const float tileSize)
		{
			if (rowIndex > 0 && matrix[colIndex][rowIndex - 1] == 0)
				AddEdge(origin.x, origin.y, origin.x + tileSize, origin.y);
			if (colIndex + 1 < matrix.size() && matrix[colIndex + 1][rowIndex] == 0)
				AddEdge(origin.x + tileSize, origin.y, origin.x + tileSize, origin.y + tileSize);
			if (rowIndex + 1 < matrix[0].size() && matrix[colIndex][rowIndex + 1] == 0)
				AddEdge(origin.x, origin.y + tileSize, origin.x + tileSize, origin.y + tileSize);
			if (colIndex > 0 && matrix[colIndex - 1][rowIndex] == 0)
				AddEdge(origin.x, origin.y, origin.x, origin.y + tileSize);
		}

		void AddEdge(float startX, float startY, float endX, float endY)
		{
			b2BodyDef edgeBodyDef = b2BodyDef();
			b2Body* edgeBody = world->CreateBody(&edgeBodyDef);

			b2FixtureDef myFixtureDef;
			myFixtureDef.density = 1;
			myFixtureDef.friction = 0;

			b2EdgeShape edgeShape;
			myFixtureDef.shape = &edgeShape;

			startX *= PhysicsValues::SCALING_FACTOR;
			startY *= PhysicsValues::SCALING_FACTOR;
			endX *= PhysicsValues::SCALING_FACTOR;
			endY *= PhysicsValues::SCALING_FACTOR;
			edgeShape.SetTwoSided(b2Vec2(startX, startY), b2Vec2(endX, endY));
			edgeShape.m_vertex0 = b2Vec2(startX - 1, startY);
			edgeShape.m_vertex3 = b2Vec2(startX + 1, startY);

			edgeBody->CreateFixture(&myFixtureDef);
		}

		/**
		* @brief Creates body, fixture and shape and adds body to box2d world
		* @spicapi
		*/
		void CreateEntity(const std::shared_ptr<spic::GameObject>& entity)
		{
			// Create body
			std::shared_ptr<spic::RigidBody> rigidBody = entity->GetComponent<spic::RigidBody>();
			b2Body* body = CreateBody(entity, rigidBody);

			// Create fixture
			if (entity->HasComponent<spic::Collider>()) {
				CreateFixture(*body, entity, rigidBody);

				// Set data
				body->GetUserData().pointer = reinterpret_cast<uintptr_t>(entity.get());
			}

			// Add to bodies
			bodies[entity->Name()] = body;
		}

		/**
		* @brief Creates box2d body with RigidBody of entity
		* @spicapi
		*/
		b2Body* CreateBody(const std::shared_ptr<spic::GameObject>& entity, const std::shared_ptr<spic::RigidBody>& rigidBody)
		{
			// cartesian origin
			const float ground_x = entity->Transform()->position.x * PhysicsValues::SCALING_FACTOR;
			const float ground_y = entity->Transform()->position.y * PhysicsValues::SCALING_FACTOR;

			b2BodyDef bodyDef;
			bodyDef.type = bodyTypeConvertions[rigidBody->BodyType()];
			bodyDef.position.Set(ground_x, ground_y); // set the starting position x and y cartesian
			bodyDef.angle = entity->Transform()->rotation;
			bodyDef.gravityScale = rigidBody->GravityScale();

			return world->CreateBody(&bodyDef);
		}

		/**
		* @brief Creates box2d fixture with RigidBody of entity
		* @spicapi
		*/
		void CreateFixture(b2Body& body, const std::shared_ptr<spic::GameObject>& entity, const std::shared_ptr<spic::RigidBody>& rigidBody) const
		{
			b2FixtureDef fixtureDef = b2FixtureDef();
			fixtureDef.density = 0.0f;
			fixtureDef.friction = 0.3f;
			fixtureDef.restitution = 0.5f;
			SetShape(fixtureDef, entity, rigidBody);
			body.CreateFixture(&fixtureDef);
		}

		/**
		* @brief Set box2d shape with Colliders of entity
		* @spicapi
		*/
		void SetShape(b2FixtureDef& fixtureDef, const std::shared_ptr<spic::GameObject>& entity, const std::shared_ptr<spic::RigidBody>& rigidBody) const
		{
			std::shared_ptr<spic::BoxCollider> boxCollider = entity->GetComponent<spic::BoxCollider>();
			if (boxCollider != nullptr) {
				const float width = boxCollider->Width() * PhysicsValues::SCALING_FACTOR;
				const float height = boxCollider->Height() * PhysicsValues::SCALING_FACTOR;
				const float hx = width / 2.0f;
				const float hy = height / 2.0f;

				b2PolygonShape* boxShape = new b2PolygonShape();
				boxShape->SetAsBox(hx, hy); // will be 0.5 x 0.5
				fixtureDef.shape = boxShape;

				const float area = width * height;
				fixtureDef.density = rigidBody->Mass() / area;
			}
			std::shared_ptr<spic::CircleCollider> circleCollider = entity->GetComponent<spic::CircleCollider>();
			if (circleCollider != nullptr) {
				b2CircleShape* circleShape = new b2CircleShape();
				circleShape->m_radius = circleCollider->Radius();
				fixtureDef.shape = circleShape;;

				const float area = spic::internal::Defaults::PI * (circleShape->m_radius * circleShape->m_radius);
				fixtureDef.density = rigidBody->Mass() / area;
			}
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
			b2Body* body = bodies[entity->Name()];

			// Get Box2D transform
			b2Vec2 b2Position = body->GetPosition();
			float b2Rotation = body->GetAngle();

			// Get entity transform
			spic::Point ePosition = entity->Transform()->position;
			ePosition.x = ePosition.x * PhysicsValues::SCALING_FACTOR;
			ePosition.y = ePosition.y * PhysicsValues::SCALING_FACTOR;
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
				body->SetGravityScale(rigidBody->GravityScale());
			}
		}

		void DrawBoxCollider(const b2Body& body, const b2PolygonShape& shape)
		{
			auto vectors = std::vector<Point>();
			const auto vertices = { shape.m_vertices[0], shape.m_vertices[1], shape.m_vertices[2], shape.m_vertices[3] };
			float maxTop = 0.0f, maxRight = 0.0f, maxBottom = 0.0f, maxLeft = 0.0f;
			for (const auto& vertice : vertices) {
				Point point = { vertice.x, vertice.y };
				vectors.emplace_back(point);
				if (vertice.y < maxTop)
					maxTop = vertice.y;
				if (vertice.x > maxRight)
					maxRight = vertice.x;
				if (vertice.y > maxBottom)
					maxBottom = vertice.y;
				if (vertice.x < maxLeft)
					maxLeft = vertice.x;
			}

			const float width = fabs(maxRight - maxLeft);
			const float height = fabs(maxTop - maxBottom);
			const auto& position = body.GetTransform().p;
			const double rotation = static_cast<double>(body.GetAngle());

			spic::Rect rect = spic::Rect(position.x / PhysicsValues::SCALING_FACTOR,
				position.y / PhysicsValues::SCALING_FACTOR,
				width / PhysicsValues::SCALING_FACTOR,
				height / PhysicsValues::SCALING_FACTOR);
			spic::internal::Rendering::DrawRect(rect, rotation, spic::Color::white());
		}

		void DrawEdgeCollider(const b2EdgeShape& shape)
		{
			Point startPoint = { shape.m_vertex1.x / PhysicsValues::SCALING_FACTOR, shape.m_vertex1.y / PhysicsValues::SCALING_FACTOR };
			Point endPoint = { shape.m_vertex2.x / PhysicsValues::SCALING_FACTOR, shape.m_vertex2.y / PhysicsValues::SCALING_FACTOR };
			spic::internal::Rendering::DrawLine(startPoint, endPoint, spic::Color::white());
		}
	};

	PhysicsExtension1::PhysicsExtension1() : physicsImpl(new PhysicsExtensionImpl1())
	{}

	PhysicsExtension1::~PhysicsExtension1() = default;

	PhysicsExtension1::PhysicsExtension1(PhysicsExtension1&&) noexcept = default;

	PhysicsExtension1& PhysicsExtension1::operator=(PhysicsExtension1&&) noexcept = default;

	PhysicsExtension1::PhysicsExtension1(const PhysicsExtension1& rhs)
		: physicsImpl(new PhysicsExtensionImpl1(*rhs.physicsImpl))
	{}

	PhysicsExtension1& PhysicsExtension1::operator=(const PhysicsExtension1& rhs)
	{
		if (this != &rhs)
			physicsImpl.reset(new PhysicsExtensionImpl1(*rhs.physicsImpl));
		return *this;
	}

	void spic::extensions::PhysicsExtension1::Reset(std::function<void(const std::shared_ptr<spic::GameObject>, const std::shared_ptr<spic::Collider>)> enterCallback,
		std::function<void(const std::shared_ptr<spic::GameObject>, const std::shared_ptr<spic::Collider>)> exitCallback,
		std::function<void(const std::shared_ptr<spic::GameObject>, const std::shared_ptr<spic::Collider>)> stayCallback)
	{
		physicsImpl->Reset();
		spic::extensions::ICollisionListener* listener = new spic::internal::extensions::Box2DCollisionListener(enterCallback, exitCallback, stayCallback);
		RegisterListener(listener);
	}

	void spic::extensions::PhysicsExtension1::AddCollisionLayer(const spic::TileLayer& collisionLayer)
	{
		physicsImpl->AddCollisionLayer(collisionLayer);
	}

	void spic::extensions::PhysicsExtension1::Update(std::vector<std::shared_ptr<spic::GameObject>> entities)
	{
		physicsImpl->Update(entities);
	}

	void spic::extensions::PhysicsExtension1::RegisterListener(ICollisionListener* listener) const
	{
		physicsImpl->RegisterListener(listener);
	}

	void spic::extensions::PhysicsExtension1::AddForce(const std::shared_ptr<GameObject>& entity, const spic::Point& forceDirection)
	{
		physicsImpl->AddForce(entity, forceDirection);
	}

	Point spic::extensions::PhysicsExtension1::GetLinearVelocity(const std::string& entityName)
	{
		return physicsImpl->GetLinearVelocity(entityName);
	}

	void spic::extensions::PhysicsExtension1::DrawColliders()
	{
		physicsImpl->DrawColliders();
	}
}