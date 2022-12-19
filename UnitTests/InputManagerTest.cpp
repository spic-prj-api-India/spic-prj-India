#include "gtest/gtest.h"

#include "InputManager.hpp"
#include "IMouseListener.hpp"
#include "IKeyListener.hpp"

class TestMouseListener : public spic::IMouseListener {
    void OnMouseMoved() override 
    {}
    void OnMouseClicked() override 
    {}
    void OnMousePressed() override 
    {}
    void OnMouseReleased() override 
    {}
};
class TestKeyListener : public spic::IKeyListener {
    void OnKeyPressed() override
    {}
    void OnKeyReleased() override
	{}
};

TEST(InputManagerTest, SubscribeSuccess) {
	//1. Arrange
	spic::internal::InputManager* inputManager = spic::internal::InputManager::GetInstance();
	inputManager->Reset();
	std::shared_ptr<TestMouseListener> mouseListener = std::make_shared<TestMouseListener>();
	std::shared_ptr<TestKeyListener> keyListener = std::make_shared<TestKeyListener>();

	//2. Act
	//3. Assert
	inputManager->Subscribe(spic::input::MouseButton::LEFT, mouseListener);
	inputManager->Subscribe(spic::input::KeyCode::A, keyListener);
}

TEST(InputManagerTest, UnSubscribeKeySuccess) {
	//1. Arrange
	spic::internal::InputManager* inputManager = spic::internal::InputManager::GetInstance();
	inputManager->Reset();
	std::shared_ptr<TestKeyListener> keyListener = std::make_shared<TestKeyListener>();
	inputManager->Subscribe(spic::input::KeyCode::A, keyListener);

	//2. Act
	//3. Assert
	inputManager->UnSubscribe(spic::input::KeyCode::A, keyListener);
}
TEST(InputManagerTest, UnSubscribeKeyFailed) {
	//1. Arrange
	spic::internal::InputManager* inputManager = spic::internal::InputManager::GetInstance();
	inputManager->Reset();
	std::shared_ptr<TestKeyListener> keyListener = std::make_shared<TestKeyListener>();

	//2. Act
	//3. Assert
	EXPECT_THROW({
		try
		{
			inputManager->UnSubscribe(spic::input::KeyCode::A, keyListener);
		}
		catch (std::exception e)
		{
			std::string errorMessage = e.what();
			EXPECT_EQ(errorMessage, "Key event is not registrered.");
			throw;
		}
		}, std::exception);
}

TEST(InputManagerTest, UnSubscribeMouseSuccess) {
	//1. Arrange
	spic::internal::InputManager* inputManager = spic::internal::InputManager::GetInstance();
	inputManager->Reset();
	std::shared_ptr<TestMouseListener> mouseListener = std::make_shared<TestMouseListener>();
	inputManager->Subscribe(spic::input::MouseButton::LEFT, mouseListener);

	//2. Act
	//3. Assert
	inputManager->UnSubscribe(spic::input::MouseButton::LEFT, mouseListener);
}
TEST(InputManagerTest, UnSubscribeMouseFailed) {
	//1. Arrange
	spic::internal::InputManager* inputManager = spic::internal::InputManager::GetInstance();
	inputManager->Reset();
	std::shared_ptr<TestMouseListener> mouseListener = std::make_shared<TestMouseListener>();

	//2. Act
	//3. Assert
	EXPECT_THROW({
		try
		{
			inputManager->UnSubscribe(spic::input::MouseButton::LEFT, mouseListener);
		}
		catch (std::exception e)
		{
			std::string errorMessage = e.what();
			EXPECT_EQ(errorMessage, "Mouse event is not registrered.");
			throw;
		}
		}, std::exception);
}