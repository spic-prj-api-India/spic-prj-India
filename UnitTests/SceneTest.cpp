#include "gtest/gtest.h"
#include "Scene.hpp"

using namespace spic;

class SceneTest : public::testing::Test
{
	protected:
		void SetUp() override
		{
			testScene = std::make_shared<spic::Scene>();
		}

		std::shared_ptr<spic::Scene> testScene;
};

TEST_F(SceneTest, GetContentsSuccess)
{
	// 1. Arrange
	std::shared_ptr<spic::GameObject> testGameObject = std::make_shared<spic::GameObject>();
	testScene->AddContent(testGameObject);

	// 2. Act
	std::vector<std::shared_ptr<GameObject>> testGameObjectList = testScene->Contents();

	// 3. Assert
	EXPECT_EQ(testGameObjectList.size(), 1);
	EXPECT_FALSE(testGameObjectList.empty());
}

TEST_F(SceneTest, AddContentSuccess) 
{
	// 1. Arrange
	std::shared_ptr<spic::GameObject> testGameObject = std::make_shared<spic::GameObject>();

	// 2. Act
	testScene->AddContent(testGameObject);

	// 3. Assert
	EXPECT_EQ(testScene->Contents().size(), 1);
	EXPECT_FALSE(testScene->Contents().empty());
}

TEST_F(SceneTest, GetCameraSuccess) 
{
	// 1. Arrange
	std::unique_ptr<spic::Camera> camera = std::make_unique<spic::Camera>();
	testScene->Camera(std::move(camera));

	// 2. Act
	
	// 3. Assert
	testScene->Camera();
}

TEST_F(SceneTest, SetCameraSuccess)
{
	// 1. Arrange
	std::unique_ptr<spic::Camera> camera = std::make_unique<spic::Camera>();
	camera->Transform(std::make_shared<spic::Transform>(spic::Point(0.0f, 0.0f), 0.0f, 1.0f));
	camera->BackgroundColor(spic::Color::blue());
	
	// 2. Act

	// 3. Assert
	testScene->Camera(std::move(camera));
}

TEST_F(SceneTest, GetUpdateSettingSuccess) 
{
	// 1. Arrange

	// 2. Act
	testScene->UpdateSetting(spic::UpdateSetting::CAMERA_VIEW);

	// 3. Assert
	EXPECT_EQ(testScene->UpdateSetting(), spic::UpdateSetting::CAMERA_VIEW);
}

TEST_F(SceneTest, SetUpdateSettingSuccess) 
{
	// 1. Arrange

	// 2. Act
	testScene->UpdateSetting(spic::UpdateSetting::CAMERA_VIEW);

	// 3. Assert
	EXPECT_EQ(testScene->UpdateSetting(), spic::UpdateSetting::CAMERA_VIEW);
}