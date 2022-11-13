#include "Input.hpp"
#include "InputManager.hpp"
#include "InputImpl.hpp"

namespace spic {
	bool Input::AnyKey()
	{
		return InputImpl::AnyKey();
	}
	bool Input::AnyKeyDown()
	{
		return InputImpl::AnyKeyDown();
	}

	Point Input::MousePosition()
	{
		return InputImpl::MousePosition();
	}

	double Input::GetAxis()
	{
		return InputImpl::GetAxis();
	}

	bool Input::GetKey(KeyCode key)
	{
		return InputImpl::GetKey(key);
	}
	bool Input::GetKeyDown(KeyCode key)
	{
		return InputImpl::GetKeyDown(key);
	}
	bool Input::GetKeyUp(KeyCode key)
	{
		return InputImpl::GetKeyUp(key);
	}

	bool Input::GetMouseButton(MouseButton which)
	{
		return InputImpl::GetMouseButton(which);
	}
	bool Input::GetMouseButtonDown(MouseButton which)
	{
		return InputImpl::GetMouseButtonDown(which);
	}
	bool Input::GetMouseButtonUp(MouseButton which)
	{
		return InputImpl::GetMouseButtonUp(which);
	}

	void Input::Subscribe(KeyCode keyEvent, const std::shared_ptr<spic::IKeyListener>& keyListener)
	{
		InputManager::GetInstance()->Subscribe(keyEvent, keyListener);
	}
	void Input::Subscribe(MouseButton mouseEvent, const std::shared_ptr<spic::IMouseListener>& mouseListener)
	{
		InputManager::GetInstance()->Subscribe(mouseEvent, mouseListener);
	}
	void Input::UnSubscribe(KeyCode keyEvent, const std::shared_ptr<spic::IKeyListener>& keyListener)
	{
		InputManager::GetInstance()->Subscribe(keyEvent, keyListener);
	}
	void Input::UnSubscribe(MouseButton mouseEvent, const std::shared_ptr<spic::IMouseListener>& mouseListener)
	{
		InputManager::GetInstance()->Subscribe(mouseEvent, mouseListener);
	}
	void Input::ResetSubscribedEvents()
	{
		InputManager::GetInstance()->Reset();
	}
}