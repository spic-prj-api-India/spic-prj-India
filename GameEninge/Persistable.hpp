#pragma once
#include "GameObject.hpp"

namespace spic {
	class Persistable: public spic::GameObject {
	public:
		Persistable() = default;
		virtual void Load() = 0;
		virtual void Save() = 0;
	};
}