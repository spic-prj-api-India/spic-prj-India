#include "gtest/gtest.h"

#include "PhysicsExtension1.hpp"

using namespace spic;

TEST(PhysicsTest, GravitySuccess) {
	//1. Arrange
	std::vector< std::shared_ptr<spic::GameObject>> entities = std::vector< std::shared_ptr<spic::GameObject>>();
	std::shared_ptr<extensions::PhysicsExtension1> PhysicsExtension1 = std::make_shared<extensions::PhysicsExtension1>();

	std::shared_ptr<spic::GameObject> box = std::make_shared<spic::GameObject>();
	std::string boxName = "box";
	std::shared_ptr<spic::Transform> boxTransform = std::make_shared<spic::Transform>();
	boxTransform->position = { 75.0f, 24.0f };
	boxTransform->rotation = 0.785f;
	boxTransform->scale = 5.0f;
	std::shared_ptr<spic::RigidBody> boxRigidBody = std::make_shared<spic::RigidBody>(1.0f, 1.0f, spic::BodyType::dynamicBody);
	box->Name(boxName);
	box->Transform(boxTransform);
	box->AddComponent<spic::RigidBody>(boxRigidBody);
	entities.emplace_back(box);
	
	//2. Act
	PhysicsExtension1->Update(entities);

	//3. Assert
	EXPECT_EQ(box->Transform()->position.y, 34.0f);
}