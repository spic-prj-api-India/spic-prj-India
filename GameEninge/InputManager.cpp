#include "InputManager.hpp"
#include "Input.hpp"
#include "GameEngine.hpp"
#include "ContainerHelper.hpp"

namespace spic::internal {
	InputManager* InputManager::pinstance_{ nullptr };
	std::mutex InputManager::mutex_;

	InputManager::InputManager() : currentMousePosition{ spic::Input::MousePosition() }, keyEvents{}, mouseEvents{}, keyListeners{}, mouseListeners{}
	{
	}

	InputManager::~InputManager()
	{
	}

	InputManager* InputManager::GetInstance()
	{
		std::lock_guard<std::mutex> lock(mutex_);
		if (pinstance_ == nullptr)
			pinstance_ = new InputManager();
		
		return pinstance_;
	}

	void InputManager::Reset()
	{
		keyEvents = {};
		mouseEvents = {};
		keyListeners = {};
		mouseListeners = {};
	}

	void InputManager::Listen()
	{
		if (spic::Input::Quit())
			spic::GameEngine::GetInstance()->Quit();

		const spic::Point newMousePosition = spic::Input::MousePosition();
		if (currentMousePosition.x != newMousePosition.x || currentMousePosition.y != newMousePosition.y) 
		{
			currentMousePosition = newMousePosition;
			TriggerMouseMoved();
		}

		for (const auto& key : ContainerHelper::GetKeys(keyEvents)) {
			bool value = keyEvents[key];
			if (spic::Input::GetKeyDown(key) && value == false) {
				keyEvents[key] = true;
				TriggerKeyPressed(key);
			}

			if (spic::Input::GetKeyUp(key) && value == true) {
				keyEvents[key] = false;
				TriggerKeyReleased(key);
			}
		}

		for (const auto& key : ContainerHelper::GetKeys(mouseEvents)) 
		{
			bool value = mouseEvents[key];
			if (spic::Input::GetMouseButtonDown(key) && value == false) {
				mouseEvents[key] = true;
				TriggerMousePressed(key);
			}

			if (spic::Input::GetMouseButtonUp(key) && value == true) {
				mouseEvents[key] = false;
				TriggerMouseReleased(key);
				TriggerMouseClicked(key);
			}
		}
	}

	void InputManager::Subscribe(spic::Input::KeyCode keyEvent, const std::shared_ptr<spic::IKeyListener> keyListener)
	{
		if (!keyEvents.count(keyEvent)) 
		{
			keyEvents[keyEvent] = false;
			keyListeners[keyEvent];
		}

		keyListeners[keyEvent].emplace_back(std::move(keyListener));
	}

	void InputManager::Subscribe(spic::Input::MouseButton mouseEvent, const std::shared_ptr<spic::IMouseListener> mouseListener)
	{
		if (!mouseListeners.count(mouseEvent)) 
		{
			mouseEvents[mouseEvent] = false;
			mouseListeners[mouseEvent];
		}

		mouseListeners[mouseEvent].emplace_back(std::move(mouseListener));
	}

	void InputManager::UnSubscribe(spic::Input::KeyCode keyEvent, const std::shared_ptr<spic::IKeyListener> keyListener)
	{
		if (!keyEvents.count(keyEvent))
			throw std::exception("Key event is not registrered.");

		keyListeners[keyEvent].erase(
			std::remove(keyListeners[keyEvent].begin(), keyListeners[keyEvent].end(), keyListener),
			keyListeners[keyEvent].end());

		if (keyListeners[keyEvent].size() == 0) 
		{
			keyListeners.erase(keyListeners.find(keyEvent));
			keyEvents.erase(keyEvents.find(keyEvent));
		}
	}

	void InputManager::UnSubscribe(spic::Input::KeyCode keyEvent)
	{
		if (!keyEvents.count(keyEvent))
			throw std::exception("Key event is not registrered.");

		keyListeners[keyEvent].clear();
		keyListeners.erase(keyListeners.find(keyEvent));
		keyEvents.erase(keyEvents.find(keyEvent));
	}

	void InputManager::UnSubscribe(spic::Input::MouseButton mouseEvent, const std::shared_ptr<spic::IMouseListener> mouseListener)
	{
		if (!mouseEvents.count(mouseEvent))
			throw std::exception("Mouse event is not registrered.");

		mouseListeners[mouseEvent].erase(
			std::remove(mouseListeners[mouseEvent].begin(), mouseListeners[mouseEvent].end(), mouseListener),
			mouseListeners[mouseEvent].end());
		if (mouseListeners[mouseEvent].size() == 0) {
			mouseListeners.erase(mouseListeners.find(mouseEvent));
			mouseEvents.erase(mouseEvents.find(mouseEvent));
		}
	}

	void InputManager::UnSubscribe(spic::Input::MouseButton mouseEvent)
	{
		if (!mouseEvents.count(mouseEvent))
			throw std::exception("Mouse event is not registrered.");

		mouseListeners[mouseEvent].clear();
		mouseListeners.erase(mouseListeners.find(mouseEvent));
		mouseEvents.erase(mouseEvents.find(mouseEvent));
	}

	void InputManager::UnSubscribeAll()
	{
		keyListeners.clear();
		mouseListeners.clear();
		keyEvents.clear();
		mouseEvents.clear();
	}

	void InputManager::TriggerKeyPressed(spic::Input::KeyCode keyEvent)
	{
		for (const std::shared_ptr<spic::IKeyListener>& keyListener : keyListeners[keyEvent]) 
			keyListener->OnKeyPressed();
	}

	void InputManager::TriggerKeyReleased(spic::Input::KeyCode keyEvent)
	{
		for (const std::shared_ptr<spic::IKeyListener>& keyListener : keyListeners[keyEvent]) 
			keyListener->OnKeyReleased();
		
	}

	void InputManager::TriggerMouseMoved()
	{
		for (const auto& key : ContainerHelper::GetKeys(mouseListeners))
			for (const std::shared_ptr<spic::IMouseListener>& mouseListener : mouseListeners[key]) 
				mouseListener->OnMouseMoved();
	}

	void InputManager::TriggerMouseClicked(spic::Input::MouseButton mouseEvent)
	{
		for (const auto& mouseListener : mouseListeners[mouseEvent]) 
			mouseListener->OnMouseClicked();
	}
	void InputManager::TriggerMousePressed(spic::Input::MouseButton mouseEvent)
	{
		for (const auto& mouseListener : mouseListeners[mouseEvent]) 
			mouseListener->OnMousePressed();
	}

	void InputManager::TriggerMouseReleased(spic::Input::MouseButton mouseEvent)
	{
		for (const auto& mouseListener : mouseListeners[mouseEvent]) 
			mouseListener->OnMouseReleased();
	}
}