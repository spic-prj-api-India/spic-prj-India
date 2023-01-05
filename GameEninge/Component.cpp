#include "Component.hpp"

namespace spic 
{
	void Component::Parent(spic::GameObject& parent)
	{
		this->parent = &parent;
	}

	spic::GameObject const* Component::Parent() const
	{
		return this->parent;
	}
}