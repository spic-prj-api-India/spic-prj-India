#ifndef COMPONENT_H_
#define COMPONENT_H_

#include "GameObject.hpp"

namespace spic {
	class GameObject;

	/**
	 * @brief Base class for all components.
	 */
	class Component {
	public:
		/**
		 * @brief Virtual destructor.
		 * @spicapi
		 */
		virtual ~Component() = default;

		void GameObject(spic::GameObject& gameObject);

		/**
		 * @brief Getter for active status.
		 * @return true if active, false otherwise.
		 * @spicapi
		 */
		bool Active() const;

		/**
		 * @brief flag New active status.
		 * @spicapi
		 */
		void Active(bool flag);


		bool IsChanged() const;
	public:
		/**
	    * @brief Parent of component
	    * @spicapi
	    */
		spic::GameObject* gameObject;
	private:
		/**
		 * @brief Active status.
		 */
		bool active;
		bool isChanged;
	};
}

#endif // COMPONENT_H_
