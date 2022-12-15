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
#include "WindowValues.hpp"
#include "RigidBody.hpp"
#include "ForceDriven.hpp"
#include "Defaults.hpp"
#include "TileLayer.hpp"
#include "Renderer.hpp"
#include "GameEngineInfo.hpp"

using namespace spic::extensions::PhysicsValues;
using namespace spic::window;

namespace spic::extensions {
	std::unique_ptr<b2World> world;
	std::map<std::string, b2Body*> bodies;
	std::map<spic::BodyType, b2BodyType> bodyTypeConvertions;

	std::map<std::string, Point> sizes;

	inline const float OFFSET = 0.00999999978f;

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
			sizes = {};
			bodies = {};
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
			world->Step(1.0f / 60.0f, int32(8), int32(3));
			// Update entities
			for (auto& entity : entities) {
				// Get body
				b2Body* body = bodies[entity->Name()];

				// Get information
				auto size = sizes[entity->Name()] - OFFSET;
				b2Vec2 position = body->GetWorldCenter();
				ConvertCoordinateToPixels(position, size);
				const float rotation = body->GetAngle();

				// Update entity
				entity->Transform()->position.x = position.x;
				entity->Transform()->position.y = position.y;
				if (!spic::TypeHelper::SharedPtrIsOfType<ForceDriven>(entity))
					entity->Transform()->rotation = rotation;
			}
		}

		void ConvertCoordinateToMeters(Point& coordinate, Point size) {
			size.x *= PIX2MET;
			size.y *= PIX2MET;
			const float x = coordinate.x - (WINDOW_WIDTH / 2.0f);
			const float y = coordinate.y - (WINDOW_HEIGHT / 2.0f);
			coordinate.x = (x * PIX2MET) + (size.x / 2.0f);
			coordinate.y = (y * PIX2MET) + (size.y / 2.0f);
		}

		void ConvertCoordinateToPixels(b2Vec2& coordinate, Point size) {
			size.x *= MET2PIX;
			size.y *= MET2PIX;
			const float x = (SCALED_WIDTH / 2.0f) + coordinate.x;
			const float y = (SCALED_HEIGHT / 2.0f) + coordinate.y;
			coordinate.x = (x * MET2PIX) - (size.x / 2.0f);
			coordinate.y = (y * MET2PIX) - (size.y / 2.0f);
		}

		void ConvertCoordinateToMeters(Point& coordinate) {
			const float x = coordinate.x - (WINDOW_WIDTH / 2.0f);
			const float y = coordinate.y - (WINDOW_HEIGHT / 2.0f);
			coordinate.x = x * PIX2MET;
			coordinate.y = y * PIX2MET;
		}

		void ConvertCoordinateToPixels(b2Vec2& coordinate) {
			const float x = (SCALED_WIDTH / 2.0f) + coordinate.x;
			const float y = (SCALED_HEIGHT / 2.0f) + coordinate.y;
			coordinate.x = x * MET2PIX;
			coordinate.y = y * MET2PIX;
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
			b2Vec2 force = { forceDirection.x * MET2PIX, forceDirection.y * MET2PIX };

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
			b2Body* currentBody = world->GetBodyList();
			while (currentBody != nullptr)
			{
				const b2Shape* shape = currentBody->GetFixtureList()->GetShape();
				if (shape == nullptr) {
					currentBody = currentBody->GetNext();
					continue;
				}
				switch (shape->GetType()) {
				case b2Shape::e_polygon:
				{
					const auto entity = reinterpret_cast<spic::GameObject*>(currentBody->GetUserData().pointer);
					auto size = sizes[entity->Name()];
					DrawBoxCollider(*currentBody, size);
				}
				break;
				case b2Shape::e_circle:
				{
					const auto entity = reinterpret_cast<spic::GameObject*>(currentBody->GetUserData().pointer);
					auto size = sizes[entity->Name()];
					DrawCircleCollider(*currentBody, size);
				}
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
				AddEdge({ origin.x, origin.y }, { origin.x + tileSize, origin.y });
			if (colIndex + 1 < matrix.size() && matrix[colIndex + 1][rowIndex] == 0)
				AddEdge({ origin.x + tileSize, origin.y }, { origin.x + tileSize, origin.y + tileSize });
			if (rowIndex + 1 < matrix[0].size() && matrix[colIndex][rowIndex + 1] == 0)
				AddEdge({ origin.x, origin.y + tileSize }, { origin.x + tileSize, origin.y + tileSize });
			if (colIndex > 0 && matrix[colIndex - 1][rowIndex] == 0)
				AddEdge({ origin.x, origin.y }, { origin.x, origin.y + tileSize });
		}

		void AddEdge(Point start, Point end)
		{
			b2BodyDef edgeBodyDef = b2BodyDef();
			b2Body* edgeBody = world->CreateBody(&edgeBodyDef);

			b2FixtureDef myFixtureDef;
			myFixtureDef.density = 1.0f;
			myFixtureDef.friction = 0.3f;

			b2EdgeShape edgeShape;
			myFixtureDef.shape = &edgeShape;

			ConvertCoordinateToMeters(start);
			ConvertCoordinateToMeters(end);

			edgeShape.SetTwoSided(b2Vec2(start.x, start.y), b2Vec2(end.x, end.y));
			edgeShape.m_vertex0 = b2Vec2(start.x - 0.01f, start.y);
			edgeShape.m_vertex3 = b2Vec2(start.x + 0.01f, start.y);

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
			const auto size = entity->GetComponent<Collider>()->Size();
			Point position = entity->Transform()->position;
			ConvertCoordinateToMeters(position, size);

			b2BodyDef bodyDef;
			bodyDef.type = bodyTypeConvertions[rigidBody->BodyType()];
			bodyDef.position.Set(position.x, position.y); // set the starting position x and y cartesian
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
			auto collider = SetShape(fixtureDef, entity, rigidBody);
			if (collider != nullptr)
				body.CreateFixture(&fixtureDef)->SetSensor(!collider->Enabled());
		}

		/**
		* @brief Set box2d shape with Colliders of entity
		* @return bool Shape is enabled
		* @spicapi
		*/
		std::shared_ptr<spic::Collider> SetShape(b2FixtureDef& fixtureDef, const std::shared_ptr<spic::GameObject>& entity, const std::shared_ptr<spic::RigidBody>& rigidBody) const
		{
			const std::shared_ptr<spic::BoxCollider> boxCollider = entity->GetComponent<spic::BoxCollider>();
			if (boxCollider != nullptr) {
				b2PolygonShape* boxShape = new b2PolygonShape();

				const float width = boxCollider->Width() * PIX2MET;
				const float height = boxCollider->Height() * PIX2MET;
				const float hx = (width / 2.0f) - boxShape->m_radius;
				const float hy = (height / 2.0f) - boxShape->m_radius;

				boxShape->SetAsBox(hx, hy); // will be 0.5 x 0.5
				fixtureDef.shape = boxShape;

				const float area = width * height;
				fixtureDef.density = rigidBody->Mass() / area;

				sizes[entity->Name()] = { width, height };
				return boxCollider;
			}
			const std::shared_ptr<spic::CircleCollider> circleCollider = entity->GetComponent<spic::CircleCollider>();
			if (circleCollider != nullptr) {
				b2CircleShape* circleShape = new b2CircleShape();

				circleShape->m_radius = circleCollider->Radius() * PIX2MET;
				fixtureDef.shape = circleShape;

				const float area = spic::internal::Defaults::PI * (circleShape->m_radius * circleShape->m_radius);
				fixtureDef.density = rigidBody->Mass() / area;

				const float diameter = circleShape->m_radius + circleShape->m_radius;
				sizes[entity->Name()] = { diameter, diameter };
				return circleCollider;
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
			b2Body* body = bodies[entity->Name()];

			// Get Box2D transform
			b2Vec2 b2Position = body->GetWorldCenter();
			float b2Rotation = body->GetAngle();

			// Get entity transform
			spic::Point ePosition = entity->Transform()->position;
			const auto size = entity->GetComponent<Collider>()->Size() - (OFFSET * MET2PIX);
			ConvertCoordinateToMeters(ePosition, size);
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

		void DrawBoxCollider(const b2Body& body, Point size)
		{
			size -= OFFSET;
			auto position = body.GetTransform().p;
			ConvertCoordinateToPixels(position, size);
			size += OFFSET;
			const double rotation = static_cast<double>(body.GetAngle());

			spic::Rect rect = spic::Rect(position.x,
				position.y,
				size.x * MET2PIX,
				size.y * MET2PIX);
			spic::internal::Rendering::DrawRect(rect, rotation, spic::Color::red());
		}

		void DrawCircleCollider(const b2Body& body, Point size)
		{
			size -= OFFSET;
			auto position = body.GetTransform().p;
			ConvertCoordinateToPixels(position, size);
			size += OFFSET;
			const float radius = (size.x / 2.0f) * MET2PIX;

			spic::Point center = { position.x + radius, position.y + radius };
			spic::internal::Rendering::DrawCircle(center, radius, spic::Color::red());
		}

		void DrawEdgeCollider(const b2EdgeShape& shape)
		{
			b2Vec2 startVec = { shape.m_vertex1.x, shape.m_vertex1.y };
			b2Vec2 endVec = { shape.m_vertex2.x, shape.m_vertex2.y };
			ConvertCoordinateToPixels(startVec);
			ConvertCoordinateToPixels(endVec);
			Point startPoint = { startVec.x, startVec.y };
			Point endPoint = { endVec.x, endVec.y };
			spic::internal::Rendering::DrawLine(startPoint, endPoint, spic::Color::red());
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