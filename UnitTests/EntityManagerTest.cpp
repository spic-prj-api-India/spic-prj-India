#include "gtest/gtest.h"
#include "EntityManager.hpp"
#include "ISystem.hpp"
#include "Scene.hpp"
#include <InputSystem.hpp>

using namespace spic;
using namespace spic::internal;
using namespace spic::internal::systems;

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
	std::shared_ptr<spic::GameObject> testGameObject1 = std::make_shared<spic::GameObject>();
	std::shared_ptr<spic::GameObject> testGameObject2 = std::make_shared<spic::GameObject>();

	entityManager->AddEntity(testGameObject1);
	entityManager->AddEntity(testGameObject2);

	// 2. Act
	std::vector<std::shared_ptr<spic::GameObject>> testEntities = entityManager->GetEntities();
	std::vector<std::shared_ptr<spic::GameObject>> expectedTestEntities {testGameObject1, testGameObject2};

	// 3. Assert
	EXPECT_EQ(testEntities, expectedTestEntities);

}

TEST_F(EntityManagerTest, AddEntitySuccess)
{
	// 1. Arrange
	std::shared_ptr<spic::GameObject> testGameObject1 = std::make_shared<spic::GameObject>();

	// 2. Act
	entityManager->AddEntity(testGameObject1);

	// 3. Assert
	EXPECT_EQ(entityManager->GetEntities().size(), 1);
}

TEST_F(EntityManagerTest, RemoveEntitySuccess)
{
	// 1. Arrange
	std::shared_ptr<spic::GameObject> testGameObject1 = std::make_shared<spic::GameObject>();
	entityManager->AddEntity(testGameObject1);

	// 2. Act
	entityManager->RemoveEntity(testGameObject1);

	// 3. Assert
	EXPECT_TRUE(entityManager->GetEntities().empty());
}

TEST_F(EntityManagerTest, SetSceneSuccess)
{
	// 1. Arrange
	std::shared_ptr<spic::Scene> testScene = std::make_shared<spic::Scene>();
	std::string testSceneName = "testScene";
	entityManager->RegisterScene(testSceneName, testScene);

	// 2. Act

	// 3. Assert
	entityManager->SetScene(testSceneName);
}

TEST_F(EntityManagerTest, DestroySceneSucces)
{
	// 1. Arrange
	std::shared_ptr<spic::GameObject> testGameObject1 = std::make_shared<spic::GameObject>();
	std::shared_ptr<spic::GameObject> testGameObject2 = std::make_shared<spic::GameObject>();
	testGameObject1->DontDestroyOnLoad();

	std::shared_ptr<spic::Scene> testScene = std::make_shared<spic::Scene>();
	std::string testSceneName = "testScene";

	testScene->AddContent(testGameObject1);
	testScene->AddContent(testGameObject2);

	entityManager->RegisterScene(testSceneName, testScene);
	entityManager->SetScene(testSceneName);

	// 2. Act
	entityManager->DestroyScene(false);

	// 3. Assert
	EXPECT_EQ(entityManager->GetEntities().size(), 1);
}

TEST_F(EntityManagerTest, ForceDestroySceneSucces){
	// 1. Arrange
	std::shared_ptr<spic::GameObject> testGameObject1 = std::make_shared<spic::GameObject>();
	std::shared_ptr<spic::GameObject> testGameObject2 = std::make_shared<spic::GameObject>();
	testGameObject1->DontDestroyOnLoad();

	std::shared_ptr<spic::Scene> testScene = std::make_shared<spic::Scene>();
	std::string testSceneName = "testScene";

	testScene->AddContent(testGameObject1);
	testScene->AddContent(testGameObject2);

	entityManager->RegisterScene(testSceneName, testScene);
	entityManager->SetScene(testSceneName);

	// 2. Act
	entityManager->DestroyScene(true);

	// 3. Assert
	EXPECT_TRUE(entityManager->GetEntities().empty());
}

TEST_F(EntityManagerTest, AddSystemSuccess) {
	// 1. Arrange
	std::unique_ptr<InputSystem> inputSystem = std::make_unique<InputSystem>();

	// 2. Act

	// 3. Assert
	entityManager->AddSystem(std::move(inputSystem));
}

TEST_F(EntityManagerTest, RemoveSystemSuccess) {
	// 1. Arrange
	std::unique_ptr<InputSystem> inputSystem = std::make_unique<InputSystem>();
	entityManager->AddSystem(std::move(inputSystem));

	// 2. Act

	// 3. Assert
	
}