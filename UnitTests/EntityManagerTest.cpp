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

			scene = std::make_shared<spic::Scene>();
			gameObject1 = std::make_shared<spic::GameObject>();
			gameObject2 = std::make_shared<spic::GameObject>();

			scene->AddContent(gameObject1);
			scene->AddContent(gameObject2);
		}

		EntityManager* entityManager;
		std::vector<std::shared_ptr<spic::GameObject>> entities;

		std::shared_ptr<spic::Scene> scene;
		std::shared_ptr<spic::GameObject> gameObject1;
		std::shared_ptr<spic::GameObject> gameObject2;
};

TEST_F(EntityManagerTest, SetSceneSuccess)
{
	// 1. Arrange

	// 2. Act

	// 3. Assert
}

TEST_F(EntityManagerTest, DestroySceneSucces)
{
	// 1. Arrange
	std::shared_ptr<spic::Scene> newScene;
	scene = newScene;
	entities.clear();

	// Continue here 

	for (auto& entity : newScene->Contents())
	{
		entities.push_back(entity);
	}

	// 2. Act
	scene = nullptr;
	for (auto& entity : entities)
	{
		if (!entity->DontDestroyOnLoad())
		{
			entities.erase(std::remove(entities.begin(), entities.end(), entity), entities.end());
		}
	}

	// 3. Assert
}

TEST_F(EntityManagerTest, ForceDestroySceneSucces){}

TEST_F(EntityManagerTest, AddSystemSuccess) {}