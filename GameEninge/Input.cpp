#include "Input.hpp"
#include "InputManager.hpp"
#include "InputImpl.hpp"

namespace spic 
{
	bool input::Quit()
	{
		return spic::internal::input::impl::Quit();
	}

	bool input::AnyKey()
	{
		return spic::internal::input::impl::AnyKey();
	}

	bool input::AnyKeyDown()
	{
		return spic::internal::input::impl::AnyKeyDown();
	}

	Point input::MousePosition()
	{
		return spic::internal::input::impl::MousePosition();
	}

	double input::GetAxis()
	{
		return spic::internal::input::impl::GetAxis();
	}

	bool input::GetKey(KeyCode key)
	{
		return spic::internal::input::impl::GetKey(key);
	}

	bool input::GetKeyDown(KeyCode key)
	{
		return spic::internal::input::impl::GetKeyDown(key);
	}

	bool input::GetKeyUp(KeyCode key)
	{
		return spic::internal::input::impl::GetKeyUp(key);
	}

	bool input::GetMouseButton(MouseButton which)
	{
		return spic::internal::input::impl::GetMouseButton(which);
	}

	bool input::GetMouseButtonDown(MouseButton which)
	{
		return spic::internal::input::impl::GetMouseButtonDown(which);
	}

	bool input::GetMouseButtonUp(MouseButton which)
	{
		return spic::internal::input::impl::GetMouseButtonUp(which);
	}

	void input::Subscribe(KeyCode keyEvent, const std::shared_ptr<spic::IKeyListener>& keyListener)
	{
		spic::internal::InputManager::GetInstance()->Subscribe(keyEvent, keyListener);
	}

	void input::Subscribe(MouseButton mouseEvent, const std::shared_ptr<spic::IMouseListener>& mouseListener)
	{
		spic::internal::InputManager::GetInstance()->Subscribe(mouseEvent, mouseListener);
	}

	void input::UnSubscribe(KeyCode keyEvent, const std::shared_ptr<spic::IKeyListener>& keyListener)
	{
		spic::internal::InputManager::GetInstance()->UnSubscribe(keyEvent, keyListener);
	}

	void input::UnSubscribe(KeyCode keyEvent)
	{
		spic::internal::InputManager::GetInstance()->UnSubscribe(keyEvent);
	}

	void input::UnSubscribe(MouseButton mouseEvent, const std::shared_ptr<spic::IMouseListener>& mouseListener)
	{
		spic::internal::InputManager::GetInstance()->UnSubscribe(mouseEvent, mouseListener);
	}

	void input::UnSubscribe(MouseButton mouseEvent)
	{
		spic::internal::InputManager::GetInstance()->UnSubscribe(mouseEvent);
	}

	void input::UnSubscribeAll()
	{
		spic::internal::InputManager::GetInstance()->UnSubscribeAll();
	}

	void input::ResetSubscribedEvents()
	{
		spic::internal::InputManager::GetInstance()->Reset();
	}
}