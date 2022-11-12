#include "gtest/gtest.h"

#include "Box2DExtension.hpp"

TEST(PhysicsTest, GravitySuccess) {
	//1. Arrange
	std::vector< std::shared_ptr<spic::GameObject>> entities = std::vector< std::shared_ptr<spic::GameObject>>();
	std::shared_ptr<extensions::Box2DExtension> box2DExtension = std::make_shared<extensions::Box2DExtension>();

	std::shared_ptr<spic::GameObject> box = std::make_shared<spic::GameObject>();
	std::string boxTag = "box";
	std::shared_ptr<spic::Transform> boxTransform = std::make_shared<spic::Transform>();
	boxTransform->position = { -2.5f, -2.5f };
	boxTransform->rotation = 45.0f;
	boxTransform->scale = 1.0f;
	std::shared_ptr<spic::RigidBody> boxRigidBody = std::make_shared<spic::RigidBody>(1.0f, 0.2f, spic::BodyType::dynamicBody);
	box->Tag(boxTag);
	box->Transform(boxTransform);
	box->AddComponent<spic::RigidBody>(boxRigidBody);
	entities.emplace_back(box);
	
	//2. Act
	box2DExtension->Update(entities);

	//3. Assert
	EXPECT_EQ(box->Transform()->position.y, -2.49666667f);
}