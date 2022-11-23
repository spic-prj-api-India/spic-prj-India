#include "gtest/gtest.h"
#include "EntityManager.hpp"
#include "ISystem.hpp"
#include "Scene.hpp"

using namespace spic;
using namespace spic::internal;

class EntityManagerTest : public::testing::Test
{
	protected:
		void SetUp() override
		{
			entityManager = EntityManager::GetInstance();
		}

		void TearDown() override
		{
			entityManager->Reset();
		}

		EntityManager* entityManager;
};

TEST_F(EntityManagerTest, RegisterSceneSuccess)
{
	// 1. Arrange
	std::shared_ptr<spic::Scene> testScene = std::make_shared<spic::Scene>();
	std::string testSceneName = "testScene";

	// 2. Act

	// 3. Assert
	entityManager->RegisterScene(testSceneName, testScene);
}

TEST_F(EntityManagerTest, RegisterSceneFailed)
{
	// 1. Arrange
	std::shared_ptr<spic::Scene> testScene = std::make_shared<spic::Scene>();
	std::string testSceneName = "testScene";
	std::shared_ptr<spic::Scene> extraTestScene = std::make_shared<spic::Scene>();

	// 2. Act
	// 3. Assert
	EXPECT_THROW
	({
		try
		{
		entityManager->RegisterScene(testSceneName, testScene);
		entityManager->RegisterScene(testSceneName, extraTestScene);
		}
		catch (std::exception e)
		{
			std::string errorMessage = e.what();
			EXPECT_EQ(errorMessage, "Scene with this name already exists.");
			throw;
		}
	}, std::exception);
}

TEST_F(EntityManagerTest, GetSceneSuccess)
{
	// 1. Arrange
	std::shared_ptr<spic::Scene> testScene = std::make_shared<spic::Scene>();
	std::string testSceneName = "testScene";

	entityManager->RegisterScene(testSceneName, testScene);
	entityManager->SetScene(testScene);

	// 2. Act
	
	// 3. Assert
	EXPECT_EQ(entityManager->GetScene(), testScene);
}

TEST_F(EntityManagerTest, GetSceneByNameSuccess)
{
	// 1. Arrange
	std::shared_ptr<spic::Scene> testScene = std::make_shared<spic::Scene>();
	std::string testSceneName = "testScene";
	entityManager->RegisterScene(testSceneName, testScene);

	// 2. Act

	// 3. Assert
	EXPECT_EQ(entityManager->GetScene(testSceneName), testScene);
}

TEST_F(EntityManagerTest, GetEntitiesSuccess)
{
	// 1. Arrange

	// 2. Act

	// 3. Assert
}

TEST_F(EntityManagerTest, RemoveEntitySuccess)
{
	// 1. Arrange

	// 2. Act

	// 3. Assert
}

TEST_F(EntityManagerTest, SetSceneSuccess)
{
	// 1. Arrange

	// 2. Act

	// 3. Assert
}

TEST_F(EntityManagerTest, DestroySceneSucces)
{
	// 1. Arrange

	// 2. Act

	// 3. Assert
}

TEST_F(EntityManagerTest, ForceDestroySceneSucces){}

TEST_F(EntityManagerTest, AddSystemSuccess) {}

TEST_F(EntityManagerTest, RemoveSystemSuccess) {}