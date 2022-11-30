#include "Input.hpp"
#include "InputManager.hpp"
#include "InputImpl.hpp"

namespace spic {
	int Input::Poll()
	{
		return spic::internal::InputImpl::Poll();
	}

	bool Input::Quit()
	{
		return spic::internal::InputImpl::Quit();
	}

	bool Input::AnyKey()
	{
		return spic::internal::InputImpl::AnyKey();
	}

	bool Input::AnyKeyDown()
	{
		return spic::internal::InputImpl::AnyKeyDown();
	}

	Point Input::MousePosition()
	{
		return spic::internal::InputImpl::MousePosition();
	}

	double Input::GetAxis()
	{
		return spic::internal::InputImpl::GetAxis();
	}

	bool Input::GetKey(KeyCode key)
	{
		return spic::internal::InputImpl::GetKey(key);
	}

	bool Input::GetKeyDown(KeyCode key)
	{
		return spic::internal::InputImpl::GetKeyDown(key);
	}

	bool Input::GetKeyUp(KeyCode key)
	{
		return spic::internal::InputImpl::GetKeyUp(key);
	}

	bool Input::GetMouseButton(MouseButton which)
	{
		return spic::internal::InputImpl::GetMouseButton(which);
	}

	bool Input::GetMouseButtonDown(MouseButton which)
	{
		return spic::internal::InputImpl::GetMouseButtonDown(which);
	}

	bool Input::GetMouseButtonUp(MouseButton which)
	{
		return spic::internal::InputImpl::GetMouseButtonUp(which);
	}

	void Input::Subscribe(KeyCode keyEvent, const std::shared_ptr<spic::IKeyListener>& keyListener)
	{
		spic::internal::InputManager::GetInstance()->Subscribe(keyEvent, keyListener);
	}

	void Input::Subscribe(MouseButton mouseEvent, const std::shared_ptr<spic::IMouseListener>& mouseListener)
	{
		spic::internal::InputManager::GetInstance()->Subscribe(mouseEvent, mouseListener);
	}

	void Input::UnSubscribe(KeyCode keyEvent, const std::shared_ptr<spic::IKeyListener>& keyListener)
	{
		spic::internal::InputManager::GetInstance()->Subscribe(keyEvent, keyListener);
	}

	void Input::UnSubscribe(MouseButton mouseEvent, const std::shared_ptr<spic::IMouseListener>& mouseListener)
	{
		spic::internal::InputManager::GetInstance()->Subscribe(mouseEvent, mouseListener);
	}

	void Input::ResetSubscribedEvents()
	{
		spic::internal::InputManager::GetInstance()->Reset();
	}
}