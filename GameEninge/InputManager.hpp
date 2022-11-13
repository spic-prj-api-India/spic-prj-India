#ifndef INPUTMANAGER_H_
#define INPUTMANAGER_H_

#include <mutex>
#include "Input.hpp"
#include <map>
#include <vector>

class InputManager {
private:
	static InputManager* pinstance_;
	static std::mutex mutex_;
protected:
	InputManager();
	~InputManager();

	spic::Point currentMousePosition;

	std::map<spic::Input::KeyCode, bool> keyEvents;
	std::map<spic::Input::MouseButton, bool> mouseEvents;
	std::map<spic::Input::KeyCode, std::vector<std::shared_ptr<spic::IKeyListener>>> keyListeners;
	std::map<spic::Input::MouseButton, std::vector<std::shared_ptr<spic::IMouseListener>>> mouseListeners;
public:
	InputManager(InputManager& other) = delete;
	InputManager(InputManager&& other) = delete;
	void operator=(const InputManager& other) = delete;
	InputManager& operator=(InputManager&& other) = delete;
	static InputManager* GetInstance();

	void Reset();
	void Listen();

	void Subscribe(spic::Input::KeyCode keyEvent, const std::shared_ptr<spic::IKeyListener>& keyListener);
	void Subscribe(spic::Input::MouseButton mouseEvent, const std::shared_ptr<spic::IMouseListener>& mouseListener);
	void UnSubscribe(spic::Input::KeyCode keyEvent, const std::shared_ptr<spic::IKeyListener>& keyListener);
	void UnSubscribe(spic::Input::MouseButton mouseEvent, const std::shared_ptr<spic::IMouseListener>& mouseListener);

	void TriggerKeyPressed(spic::Input::KeyCode key);
	void TriggerKeyReleased(spic::Input::KeyCode key);

	void TriggerMouseMoved();
	void TriggerMouseClicked(spic::Input::MouseButton mouseEvent);
	void TriggerMousePressed(spic::Input::MouseButton mouseEvent);
	void TriggerMouseReleased(spic::Input::MouseButton mouseEvent);
private:
};

#endif // INPUTMANAGER_H_