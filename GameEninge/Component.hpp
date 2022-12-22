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
		Component() = default;
		/**
		 * @brief Virtual destructor.
		 * @spicapi
		 */
		virtual ~Component() = default;

		Component(const Component& other) = default; // copy constructor
		Component(Component&& other) noexcept = default; // move constructor
		virtual Component& operator=(const Component& other) = default; // copy assignment
		virtual Component& operator=(Component&& other) noexcept = default;// move assignment

		void Parent(spic::GameObject& gameObject);


		bool IsChanged() const;
	public:
		/**
		* @brief Parent of component
		* @spicapi
		*/
		spic::GameObject* gameObject;
	};
}

#endif // COMPONENT_H_