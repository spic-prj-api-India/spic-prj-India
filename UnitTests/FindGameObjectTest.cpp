#include "gtest/gtest.h"

#include "GameObject.hpp"
#include "Scene.hpp"
#include "GameEngine.hpp"

class TestGameObject : public spic::GameObject {
public:
	TestGameObject() : GameObject()
	{}

	TestGameObject(const std::string& name) : GameObject(name)
	{}
};

TEST(FindGameObjectTest, FindSuccess) {
	//1. Arrange
	std::shared_ptr<spic::GameObject> gameObject = std::make_shared<spic::GameObject>("player1");
	std::shared_ptr<spic::Scene> scene = std::make_shared<spic::Scene>();
	scene->AddContent(gameObject);
	spic::GameEngine::GetInstance()->LoadScene(scene);

	//2. Act
	std::shared_ptr<spic::GameObject> foundGameObject = spic::GameObject::Find("player1");

	//3. Assert
	EXPECT_NE(foundGameObject, nullptr);
	EXPECT_EQ(foundGameObject, gameObject);
}

TEST(FindGameObjectTest, FindFailed) {
	//1. Arrange
	std::shared_ptr<spic::GameObject> gameObject = std::make_shared<spic::GameObject>("player2");
	std::shared_ptr<spic::Scene> scene = std::make_shared<spic::Scene>();
	scene->AddContent(gameObject);
	spic::GameEngine::GetInstance()->LoadScene(scene);

	//2. Act
	std::shared_ptr<spic::GameObject> foundGameObject = spic::GameObject::Find("player1");

	//3. Assert
	EXPECT_EQ(foundGameObject, nullptr);
	EXPECT_NE(foundGameObject, gameObject);
}

TEST(FindGameObjectTest, FindWithTagSuccess) {
	//1. Arrange
	std::shared_ptr<spic::GameObject> gameObject = std::make_shared<spic::GameObject>("player1");
	std::string tag = "player";
	gameObject->Tag(tag);
	std::shared_ptr<spic::Scene> scene = std::make_shared<spic::Scene>();
	scene->AddContent(gameObject);
	spic::GameEngine::GetInstance()->LoadScene(scene);

	//2. Act
	std::shared_ptr<spic::GameObject> foundGameObject = spic::GameObject::FindWithTag("player");

	//3. Assert
	EXPECT_NE(foundGameObject, nullptr);
	EXPECT_EQ(foundGameObject, gameObject);
}

TEST(FindGameObjectTest, FindWithTagFailed) {
	//1. Arrange
	std::shared_ptr<spic::GameObject> gameObject = std::make_shared<spic::GameObject>("obstacle1");
	std::string tag = "obstacle";
	gameObject->Tag(tag);
	std::shared_ptr<spic::Scene> scene = std::make_shared<spic::Scene>();
	scene->AddContent(gameObject);
	spic::GameEngine::GetInstance()->LoadScene(scene);

	//2. Act
	std::shared_ptr<spic::GameObject> foundGameObject = spic::GameObject::FindWithTag("player");

	//3. Assert
	EXPECT_EQ(foundGameObject, nullptr);
	EXPECT_NE(foundGameObject, gameObject);
}

TEST(FindGameObjectTest, FindGameObjectsWithTagSuccess) {
	//1. Arrange
	std::shared_ptr<spic::GameObject> gameObject1 = std::make_shared<spic::GameObject>("player1");
	std::shared_ptr<spic::GameObject> gameObject2 = std::make_shared<spic::GameObject>("player2");
	std::string tag = "player";
	gameObject1->Tag(tag);
	gameObject2->Tag(tag);
	std::shared_ptr<spic::Scene> scene = std::make_shared<spic::Scene>();
	scene->AddContent(gameObject1);
	scene->AddContent(gameObject2);
	spic::GameEngine::GetInstance()->LoadScene(scene);

	//2. Act
	std::vector<std::shared_ptr<spic::GameObject>> foundGameObjects = spic::GameObject::FindGameObjectsWithTag("player");

	//3. Assert
	EXPECT_EQ(foundGameObjects.size(), 2);
	EXPECT_EQ(foundGameObjects[0], gameObject1);
	EXPECT_EQ(foundGameObjects[1], gameObject2);
}

TEST(FindGameObjectTest, FindGameObjectsWithTagFailed) {
	//1. Arrange
	std::shared_ptr<spic::GameObject> gameObject1 = std::make_shared<spic::GameObject>("player1");
	std::shared_ptr<spic::GameObject> gameObject2 = std::make_shared<spic::GameObject>("obstacle1");
	std::string tag1 = "player";
	std::string tag2 = "obstacle";
	gameObject1->Tag(tag1);
	gameObject2->Tag(tag2);
	std::shared_ptr<spic::Scene> scene = std::make_shared<spic::Scene>();
	scene->AddContent(gameObject1);
	scene->AddContent(gameObject2);
	spic::GameEngine::GetInstance()->LoadScene(scene);

	//2. Act
	std::vector<std::shared_ptr<spic::GameObject>> foundGameObjects = spic::GameObject::FindGameObjectsWithTag("player");

	//3. Assert
	EXPECT_NE(foundGameObjects.size(), 2);
	EXPECT_EQ(foundGameObjects[0], gameObject1);
}


TEST(FindGameObjectTest, FindObjectOfTypeSuccess) {
	//1. Arrange
	std::shared_ptr<TestGameObject> gameObject1 = std::make_shared<TestGameObject>("player1");
	std::shared_ptr<spic::GameObject> gameObject2 = std::make_shared<spic::GameObject>("player2");
	std::string tag = "player";
	gameObject1->Tag(tag);
	gameObject2->Tag(tag);
	std::shared_ptr<spic::Scene> scene = std::make_shared<spic::Scene>();
	scene->AddContent(gameObject1);
	scene->AddContent(gameObject2);
	spic::GameEngine::GetInstance()->LoadScene(scene);

	//2. Act
	std::shared_ptr<spic::GameObject> foundGameObject = spic::GameObject::FindObjectOfType<TestGameObject>(true);

	//3. Assert
	EXPECT_NE(foundGameObject, nullptr);
	EXPECT_EQ(foundGameObject, gameObject1);
}

TEST(FindGameObjectTest, FindObjectOfTypeFailed) {
	//1. Arrange
	std::shared_ptr<spic::GameObject> gameObject1 = std::make_shared<spic::GameObject>("player1");
	std::shared_ptr<spic::GameObject> gameObject2 = std::make_shared<spic::GameObject>("obstacle1");
	std::string tag1 = "player";
	std::string tag2 = "obstacle";
	gameObject1->Tag(tag1);
	gameObject2->Tag(tag2);
	std::shared_ptr<spic::Scene> scene = std::make_shared<spic::Scene>();
	scene->AddContent(gameObject1);
	scene->AddContent(gameObject2);
	spic::GameEngine::GetInstance()->LoadScene(scene);

	//2. Act
	std::shared_ptr<spic::GameObject> foundGameObject = spic::GameObject::FindObjectOfType<TestGameObject>(true);

	//3. Assert
	EXPECT_EQ(foundGameObject, nullptr);
	EXPECT_NE(foundGameObject, gameObject1);
}

TEST(FindGameObjectTest, FindObjectsOfTypeSuccess) {
	//1. Arrange
	std::shared_ptr<TestGameObject> gameObject1 = std::make_shared<TestGameObject>("player1");
	std::shared_ptr<TestGameObject> gameObject2 = std::make_shared<TestGameObject>("player2");
	std::string tag = "player";
	gameObject1->Tag(tag);
	gameObject2->Tag(tag);
	std::shared_ptr<spic::Scene> scene = std::make_shared<spic::Scene>();
	scene->AddContent(gameObject1);
	scene->AddContent(gameObject2);
	spic::GameEngine::GetInstance()->LoadScene(scene);

	//2. Act
	std::vector<std::shared_ptr<TestGameObject>> foundGameObjects = spic::GameObject::FindObjectsOfType<TestGameObject>(true);

	//3. Assert
	EXPECT_EQ(foundGameObjects.size(), 2);
	EXPECT_EQ(foundGameObjects[0], gameObject1);
	EXPECT_EQ(foundGameObjects[1], gameObject2);
}

TEST(FindGameObjectTest, FindObjectsOfTypeFailed) {
	//1. Arrange
	std::shared_ptr<TestGameObject> gameObject1 = std::make_shared<TestGameObject>("player1");
	std::shared_ptr<spic::GameObject> gameObject2 = std::make_shared<spic::GameObject>("obstacle1");
	std::string tag1 = "player";
	std::string tag2 = "obstacle";
	gameObject1->Tag(tag1);
	gameObject2->Tag(tag2);
	std::shared_ptr<spic::Scene> scene = std::make_shared<spic::Scene>();
	scene->AddContent(gameObject1);
	scene->AddContent(gameObject2);
	spic::GameEngine::GetInstance()->LoadScene(scene);

	//2. Act
	std::vector<std::shared_ptr<TestGameObject>> foundGameObjects = spic::GameObject::FindObjectsOfType<TestGameObject>(true);

	//3. Assert
	EXPECT_NE(foundGameObjects.size(), 2);
	EXPECT_EQ(foundGameObjects[0], gameObject1);
}