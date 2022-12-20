#include "gtest/gtest.h"

#include "GameEngine.hpp"
#include "PhysicsExtension1.hpp"

using namespace spic;
TEST(ExtensionTest, AddExtensionSuccess) {
	//1. Arrange
	spic::GameEngine* engine = spic::GameEngine::GetInstance();
	std::shared_ptr<extensions::PhysicsExtension1> extension = std::make_shared<extensions::PhysicsExtension1>();

	//2. Act
	engine->AddExtension(extension);

	//3. Assert
	bool exists = engine->HasExtension<extensions::PhysicsExtension1>();
	auto weakPtrExtension = engine->GetExtension<extensions::PhysicsExtension1>();
	auto compareExtension = weakPtrExtension.lock();
	EXPECT_TRUE(exists);
	EXPECT_EQ(typeid(compareExtension).name(), typeid(extension).name());
}
TEST(ExtensionTest, RemoveExtensionSuccess) {
	//1. Arrange
	spic::GameEngine* engine = spic::GameEngine::GetInstance();
	std::shared_ptr<extensions::PhysicsExtension1> extension = std::make_shared<extensions::PhysicsExtension1>();

	//2. Act
	engine->AddExtension(std::move(extension));
	engine->RemoveExtension<extensions::PhysicsExtension1>();

	//3. Assert
	bool exists = engine->HasExtension<extensions::PhysicsExtension1>();
	auto weakPtrExtension = engine->GetExtension<extensions::PhysicsExtension1>();
	auto compareExtension = weakPtrExtension.lock();
	EXPECT_FALSE(exists);
	EXPECT_EQ(extension, nullptr);
	EXPECT_EQ(compareExtension, nullptr);
}

