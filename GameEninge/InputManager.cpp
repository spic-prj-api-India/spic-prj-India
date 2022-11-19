#include "InputManager.hpp"
#include "Input.hpp"
#include "GameEngine.hpp"

namespace spic::internal {
	InputManager* InputManager::pinstance_{ nullptr };
	std::mutex InputManager::mutex_;

	InputManager::InputManager() : currentMousePosition{ spic::Input::MousePosition() }, keyEvents{}, mouseEvents{}, keyListeners{}, mouseListeners{}
	{}

	InputManager::~InputManager()
	{}

	InputManager* InputManager::GetInstance()
	{
		std::lock_guard<std::mutex> lock(mutex_);
		if (pinstance_ == nullptr)
		{
			pinstance_ = new InputManager();
		}
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
		if (currentMousePosition.x != newMousePosition.x || currentMousePosition.y != newMousePosition.y) {
			currentMousePosition = newMousePosition;
			TriggerMouseMoved();
		}
		for (const auto& keyEvent : keyEvents) {
			if (spic::Input::GetKeyDown(keyEvent.first) && keyEvents[keyEvent.first] == false) {
				keyEvents[keyEvent.first] = true;
				TriggerKeyPressed(keyEvent.first);
			}
			if (spic::Input::GetKeyUp(keyEvent.first) && keyEvents[keyEvent.first] == true) {
				keyEvents[keyEvent.first] = false;
				TriggerKeyReleased(keyEvent.first);
			}
		}
		for (const auto& mouseEvent : mouseEvents) {
			if (spic::Input::GetMouseButtonDown(mouseEvent.first) && mouseEvents[mouseEvent.first] == false) {
				mouseEvents[mouseEvent.first] = true;
				TriggerMousePressed(mouseEvent.first);
			}
			if (spic::Input::GetMouseButtonUp(mouseEvent.first) && mouseEvents[mouseEvent.first] == true) {
				mouseEvents[mouseEvent.first] = false;
				TriggerMouseReleased(mouseEvent.first);
				TriggerMouseClicked(mouseEvent.first);
			}
		}
	}

	void InputManager::Subscribe(spic::Input::KeyCode keyEvent, const std::shared_ptr<spic::IKeyListener>& keyListener)
	{
		if (!keyEvents.count(keyEvent)) {
			keyEvents[keyEvent] = false;
			keyListeners[keyEvent];
		}
		keyListeners[keyEvent].emplace_back(keyListener);
	}

	void InputManager::Subscribe(spic::Input::MouseButton mouseEvent, const std::shared_ptr<spic::IMouseListener>& mouseListener)
	{
		if (!mouseListeners.count(mouseEvent)) {
			mouseEvents[mouseEvent] = false;
			mouseListeners[mouseEvent];
		}
		mouseListeners[mouseEvent].emplace_back(mouseListener);
	}

	void InputManager::UnSubscribe(spic::Input::KeyCode keyEvent, const std::shared_ptr<spic::IKeyListener>& keyListener)
	{
		if (!keyEvents.count(keyEvent))
			throw std::exception("Key event is not registrered.");
		keyListeners[keyEvent].erase(
			std::remove(keyListeners[keyEvent].begin(), keyListeners[keyEvent].end(), keyListener),
			keyListeners[keyEvent].end());
		if (keyListeners[keyEvent].size() == 0) {
			keyListeners.erase(keyListeners.find(keyEvent));
			keyEvents.erase(keyEvents.find(keyEvent));
		}
	}

	void InputManager::UnSubscribe(spic::Input::MouseButton mouseEvent, const std::shared_ptr<spic::IMouseListener>& mouseListener)
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

	void InputManager::TriggerKeyPressed(spic::Input::KeyCode keyEvent)
	{
		for (const std::shared_ptr<spic::IKeyListener>& keyListener : keyListeners[keyEvent]) {
			keyListener->OnKeyPressed();
		}
	}

	void InputManager::TriggerKeyReleased(spic::Input::KeyCode keyEvent)
	{
		for (const std::shared_ptr<spic::IKeyListener>& keyListener : keyListeners[keyEvent]) {
			keyListener->OnKeyReleased();
		}
	}

	void InputManager::TriggerMouseMoved() const
	{
		for (const auto& mousePair : mouseListeners) {
			for (const std::shared_ptr<spic::IMouseListener>& mouseListener : mousePair.second) {
				mouseListener->OnMouseMoved();
			}
		}
	}

	void InputManager::TriggerMouseClicked(spic::Input::MouseButton mouseEvent)
	{
		for (const std::shared_ptr<spic::IMouseListener>& mouseListener : mouseListeners[mouseEvent]) {
			mouseListener->OnMouseClicked();
		}
	}
	void InputManager::TriggerMousePressed(spic::Input::MouseButton mouseEvent)
	{
		for (const std::shared_ptr<spic::IMouseListener>& mouseListener : mouseListeners[mouseEvent]) {
			mouseListener->OnMousePressed();
		}
	}

	void InputManager::TriggerMouseReleased(spic::Input::MouseButton mouseEvent)
	{
		for (const std::shared_ptr<spic::IMouseListener>& mouseListener : mouseListeners[mouseEvent]) {
			mouseListener->OnMouseReleased();
		}
	}
}