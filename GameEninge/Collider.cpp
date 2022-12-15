#include "Collider.hpp"

using namespace spic;

Collider::Collider()
{
	enabled = true;
}

bool Collider::Enabled() const
{
	return enabled;
}

void Collider::Disable()
{
	enabled = false;
}

void Collider::Enable() {
	enabled = true;
}