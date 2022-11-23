#include "IPhysicsExtension.hpp"

namespace spic::extensions {
	IPhysicsExtension::IPhysicsExtension() = default;

	IPhysicsExtension::~IPhysicsExtension() = default;

	IPhysicsExtension::IPhysicsExtension(IPhysicsExtension&& rhs) noexcept
	{}

	IPhysicsExtension& IPhysicsExtension::operator=(IPhysicsExtension&& rhs) noexcept
	{ 
		return rhs; 
	}

	IPhysicsExtension::IPhysicsExtension(const IPhysicsExtension& rhs)
	{}

	IPhysicsExtension& IPhysicsExtension::operator=(const IPhysicsExtension& rhs) 
	{ 
		return *this; 
	}
}