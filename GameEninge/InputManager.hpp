#ifndef INPUTMANAGER_H_
#define INPUTMANAGER_H_

#include <mutex>
#include "Input.hpp"
#include <map>
#include <vector>

namespace spic::internal {
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

		/**
		* @brief Removes all listeners
		* @spicapi
		*/
		void Reset();

		/**
		* @brief Listen to key and mouse listeners
		* @spicapi
		*/
		void Listen();

		/**
		* @brief Subscribes a key listener for a specific key event
		* @spicapi
		*/
		void Subscribe(spic::Input::KeyCode keyEvent, const std::shared_ptr<spic::IKeyListener>& keyListener);

		/**
		* @brief Subscribes a mouse listener for a specific mouse event
		* @spicapi
		*/
		void Subscribe(spic::Input::MouseButton mouseEvent, const std::shared_ptr<spic::IMouseListener>& mouseListener);

		/**
		* @brief Unsubscribes a key listener for a specific key event
		* @spicapi
		*/
		void UnSubscribe(spic::Input::KeyCode keyEvent, const std::shared_ptr<spic::IKeyListener>& keyListener);

		/**
		* @brief Unsubscribes all listeners for a specific key event
		* @spicapi
		*/
		void UnSubscribe(spic::Input::KeyCode keyEvent);

		/**
		* @brief Unsubscribes a mouse listener for a specific mouse event
		* @spicapi
		*/
		void UnSubscribe(spic::Input::MouseButton mouseEvent, const std::shared_ptr<spic::IMouseListener>& mouseListener);
	
		/**
		* @brief Unsubscribes all listeners for a specific mouse event
		* @spicapi
		*/
		void UnSubscribe(spic::Input::MouseButton mouseEvent);

		/**
		* @brief Unsubscribes all listeners
		* @spicapi
		*/
		void UnSubscribeAll();
	private:
		/**
		* @brief Calls method OnKeyPressed of all key listeners for specific key event
		* @spicapi
		*/
		void TriggerKeyPressed(spic::Input::KeyCode keyEvent);

		/**
		* @brief Calls method OnKeyPressed of all key listeners for specific key event
		* @spicapi
		*/
		void TriggerKeyReleased(spic::Input::KeyCode keyEvent);

		/**
		* @brief Calls method OnMouseMoved of all mouse listeners
		* @spicapi
		*/
		void TriggerMouseMoved();

		/**
		* @brief Calls method OnMouseClicked of all mouse listeners for specific mouse event
		* @spicapi
		*/
		void TriggerMouseClicked(spic::Input::MouseButton mouseEvent);

		/**
		* @brief Calls method OnMousePressed of all mouse listeners for specific mouse event
		* @spicapi
		*/
		void TriggerMousePressed(spic::Input::MouseButton mouseEvent);

		/**
		* @brief Calls method OnMouseReleased of all mouse listeners for specific mouse event
		* @spicapi
		*/
		void TriggerMouseReleased(spic::Input::MouseButton mouseEvent);
	};
}

#endif // INPUTMANAGER_H_