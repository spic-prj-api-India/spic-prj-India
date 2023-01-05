#include "Component.hpp"

namespace spic 
{
	void Component::Parent(spic::GameObject& gameObject)
	{
		this->gameObject = &gameObject;
	}

	spic::GameObject* Component::Parent() const
	{
		return this->gameObject;
	}
}