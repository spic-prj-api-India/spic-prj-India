#include "Component.hpp"

namespace spic {
	void Component::GameObject(spic::GameObject& gameObject)
	{
		this->gameObject = &gameObject;
	}

	bool Component::Active() const
	{
		return this->active;
	}

	/**
	 * @brief flag New active status.
	 * @spicapi
	 */
	void Component::Active(bool flag)
	{
		this->active = flag;
	}


	bool Component::IsChanged() const
	{
		return this->isChanged;
	}
}