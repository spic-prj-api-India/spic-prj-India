#include "InputManager.hpp"
#include "Input.hpp"
#include "GameEngine.hpp"
#include "ContainerHelper.hpp"

namespace spic::internal {
	InputManager* InputManager::pinstance_{ nullptr };
	std::mutex InputManager::mutex_;

	InputManager::InputManager() : currentMousePosition{ spic::input::MousePosition() }, keyEvents{}, mouseEvents{}, keyListeners{}, mouseListeners{}
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
		if (spic::input::Quit())
			spic::GameEngine::GetInstance()->Quit();

		const spic::Point newMousePosition = spic::input::MousePosition();
		if (currentMousePosition.x != newMousePosition.x || currentMousePosition.y != newMousePosition.y) 
		{
			currentMousePosition = newMousePosition;
			TriggerMouseMoved();
		}

		for (const auto& key : helper_functions::container::GetKeys(keyEvents)) {
			bool value = keyEvents[key];
			if (spic::input::GetKeyDown(key) && value == false) {
				keyEvents[key] = true;
				TriggerKeyPressed(key);
			}

			if (spic::input::GetKeyUp(key) && value == true) {
				keyEvents[key] = false;
				TriggerKeyReleased(key);
			}
		}

		for (const auto& key : helper_functions::container::GetKeys(mouseEvents))
		{
			bool value = mouseEvents[key];
			if (spic::input::GetMouseButtonDown(key) && value == false) {
				mouseEvents[key] = true;
				TriggerMousePressed(key);
			}

			if (spic::input::GetMouseButtonUp(key) && value == true) {
				mouseEvents[key] = false;
				TriggerMouseReleased(key);
				TriggerMouseClicked(key);
			}
		}
	}

	void InputManager::Subscribe(spic::input::KeyCode keyEvent, const std::shared_ptr<spic::IKeyListener> keyListener)
	{
		if (!keyEvents.count(keyEvent)) 
		{
			keyEvents[keyEvent] = false;
			keyListeners[keyEvent];
		}

		keyListeners[keyEvent].emplace_back(std::move(keyListener));
	}

	void InputManager::Subscribe(spic::input::MouseButton mouseEvent, const std::shared_ptr<spic::IMouseListener> mouseListener)
	{
		if (!mouseListeners.count(mouseEvent)) 
		{
			mouseEvents[mouseEvent] = false;
			mouseListeners[mouseEvent];
		}

		mouseListeners[mouseEvent].emplace_back(std::move(mouseListener));
	}

	void InputManager::UnSubscribe(spic::input::KeyCode keyEvent, const std::shared_ptr<spic::IKeyListener> keyListener)
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

	void InputManager::UnSubscribe(spic::input::KeyCode keyEvent)
	{
		if (!keyEvents.count(keyEvent))
			throw std::exception("Key event is not registrered.");

		keyListeners[keyEvent].clear();
		keyListeners.erase(keyListeners.find(keyEvent));
		keyEvents.erase(keyEvents.find(keyEvent));
	}

	void InputManager::UnSubscribe(spic::input::MouseButton mouseEvent, const std::shared_ptr<spic::IMouseListener> mouseListener)
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

	void InputManager::UnSubscribe(spic::input::MouseButton mouseEvent)
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

	void InputManager::TriggerKeyPressed(spic::input::KeyCode keyEvent)
	{
		for (const std::shared_ptr<spic::IKeyListener>& keyListener : keyListeners[keyEvent]) 
			keyListener->OnKeyPressed();
	}

	void InputManager::TriggerKeyReleased(spic::input::KeyCode keyEvent)
	{
		for (const std::shared_ptr<spic::IKeyListener>& keyListener : keyListeners[keyEvent]) 
			keyListener->OnKeyReleased();
		
	}

	void InputManager::TriggerMouseMoved()
	{
		for (const auto& key : helper_functions::container::GetKeys(mouseListeners))
			for (const std::shared_ptr<spic::IMouseListener>& mouseListener : mouseListeners[key]) 
				mouseListener->OnMouseMoved();
	}

	void InputManager::TriggerMouseClicked(spic::input::MouseButton mouseEvent)
	{
		for (const auto& mouseListener : mouseListeners[mouseEvent]) 
			mouseListener->OnMouseClicked();
	}
	void InputManager::TriggerMousePressed(spic::input::MouseButton mouseEvent)
	{
		for (const auto& mouseListener : mouseListeners[mouseEvent]) 
			mouseListener->OnMousePressed();
	}

	void InputManager::TriggerMouseReleased(spic::input::MouseButton mouseEvent)
	{
		for (const auto& mouseListener : mouseListeners[mouseEvent]) 
			mouseListener->OnMouseReleased();
	}
}