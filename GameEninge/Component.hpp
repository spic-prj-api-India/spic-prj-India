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

		/**
		 * @brief Sets the parent of this component
		 * @param gameObject 
		 * @sharedapi
		*/
		void Parent(spic::GameObject& gameObject);

		/**
		 * @brief Gets parent of this component
		 * @return Parent gameobject
		*/
		spic::GameObject* Parent() const;
	
	protected:
		/**
		* @brief Parent of component
		* @spicapi
		*/
		spic::GameObject* gameObject;
	};
}

#endif // COMPONENT_H_