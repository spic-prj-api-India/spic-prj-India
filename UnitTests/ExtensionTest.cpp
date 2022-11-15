#include "gtest/gtest.h"

#include "GameEngine.hpp"
#include "Box2DExtension.hpp"

using namespace spic;
TEST(ExtensionTest, AddExtensionSuccess) {
	//1. Arrange
	spic::GameEngine* engine = spic::GameEngine::GetInstance();
	std::shared_ptr<extensions::Box2DExtension> extension = std::make_shared<extensions::Box2DExtension>();

	//2. Act
	engine->AddExtension(extension);

	//3. Assert
	bool exists = engine->HasExtension<extensions::Box2DExtension>();
	auto weakPtrExtension = engine->GetExtension<extensions::Box2DExtension>();
	auto compareExtension = weakPtrExtension.lock();
	EXPECT_TRUE(exists);
	EXPECT_EQ(typeid(compareExtension).name(), typeid(extension).name());
}
TEST(ExtensionTest, RemoveExtensionSuccess) {
	//1. Arrange
	spic::GameEngine* engine = spic::GameEngine::GetInstance();
	std::shared_ptr<extensions::Box2DExtension> extension = std::make_shared<extensions::Box2DExtension>();

	//2. Act
	engine->AddExtension(std::move(extension));
	engine->RemoveExtension<extensions::Box2DExtension>();

	//3. Assert
	bool exists = engine->HasExtension<extensions::Box2DExtension>();
	auto weakPtrExtension = engine->GetExtension<extensions::Box2DExtension>();
	auto compareExtension = weakPtrExtension.lock();
	EXPECT_FALSE(exists);
	EXPECT_EQ(extension, nullptr);
	EXPECT_EQ(compareExtension, nullptr);
}

