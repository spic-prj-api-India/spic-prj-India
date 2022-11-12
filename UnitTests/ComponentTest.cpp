#include "gtest/gtest.h"

#include "GameObject.hpp"
#include <BoxCollider.hpp>
#include <CircleCollider.hpp>

TEST(ComponentTest, AddComponentSuccess) {
	//1. Arrange
	spic::GameObject gameObject = spic::GameObject();
	std::shared_ptr<spic::BoxCollider> boxCollider1 = std::make_shared<spic::BoxCollider>();
	std::shared_ptr<spic::BoxCollider> boxCollider2 = std::make_shared<spic::BoxCollider>();
	std::shared_ptr<spic::CircleCollider> circleCollider = std::make_shared<spic::CircleCollider>();

	//2. Act
	gameObject.AddComponent<spic::BoxCollider>(boxCollider1);
	gameObject.AddComponent<spic::BoxCollider>(boxCollider2);
	gameObject.AddComponent<spic::CircleCollider>(circleCollider);

	//3. Assert
	auto components = gameObject.GetComponents<spic::Component>();
	EXPECT_EQ(components.size(), 3);
}
TEST(ComponentTest, GetComponentsSuccess) {
	//1. Arrange
	spic::GameObject gameObject = spic::GameObject();
	std::shared_ptr<spic::BoxCollider> boxCollider1 = std::make_shared<spic::BoxCollider>();
	std::shared_ptr<spic::BoxCollider> boxCollider2 = std::make_shared<spic::BoxCollider>();
	std::shared_ptr<spic::CircleCollider> circleCollider = std::make_shared<spic::CircleCollider>();

	gameObject.AddComponent<spic::BoxCollider>(boxCollider1);
	gameObject.AddComponent<spic::BoxCollider>(boxCollider2);
	gameObject.AddComponent<spic::CircleCollider>(circleCollider);

	//2. Act
	auto components = gameObject.GetComponents<spic::BoxCollider>();

	//3. Assert
	EXPECT_EQ(components.size(), 2);
	EXPECT_EQ(typeid(components[0]).name(), typeid(boxCollider1).name());
	EXPECT_EQ(typeid(components[1]).name(), typeid(boxCollider2).name());
}
TEST(ComponentTest, GetComponentSuccess) {
	//1. Arrange
	spic::GameObject gameObject = spic::GameObject();
	std::shared_ptr<spic::BoxCollider> boxCollider1 = std::make_shared<spic::BoxCollider>();
	std::shared_ptr<spic::BoxCollider> boxCollider2 = std::make_shared<spic::BoxCollider>();
	std::shared_ptr<spic::CircleCollider> circleCollider = std::make_shared<spic::CircleCollider>();

	gameObject.AddComponent<spic::BoxCollider>(boxCollider1);
	gameObject.AddComponent<spic::BoxCollider>(boxCollider2);
	gameObject.AddComponent<spic::CircleCollider>(circleCollider);

	//2. Act
	auto component = gameObject.GetComponent<spic::BoxCollider>();

	//3. Assert
	EXPECT_EQ(typeid(component).name(), typeid(boxCollider1).name());
}

TEST(ComponentTest, HasComponentTrue) {
	//1. Arrange
	spic::GameObject gameObject = spic::GameObject();
	std::shared_ptr<spic::BoxCollider> boxCollider1 = std::make_shared<spic::BoxCollider>();
	std::shared_ptr<spic::BoxCollider> boxCollider2 = std::make_shared<spic::BoxCollider>();
	std::shared_ptr<spic::CircleCollider> circleCollider = std::make_shared<spic::CircleCollider>();

	gameObject.AddComponent<spic::BoxCollider>(boxCollider1);
	gameObject.AddComponent<spic::BoxCollider>(boxCollider2);
	gameObject.AddComponent<spic::CircleCollider>(circleCollider);

	//2. Act
	bool hasBoxCollider = gameObject.HasComponent<spic::BoxCollider>();
	bool hasCircleCollider = gameObject.HasComponent<spic::CircleCollider>();

	//3. Assert
	EXPECT_TRUE(hasBoxCollider);
	EXPECT_TRUE(hasCircleCollider);
}

TEST(ComponentTest, HasComponentFalse) {
	//1. Arrange
	spic::GameObject gameObject = spic::GameObject();

	//2. Act
	bool hasBoxCollider = gameObject.HasComponent<spic::BoxCollider>();

	//3. Assert
	EXPECT_FALSE(hasBoxCollider);
}