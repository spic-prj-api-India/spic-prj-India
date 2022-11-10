#pragma once
#include "ISystem.hpp"

namespace systems {
	class ScriptSystem :
		public ISystem
	{
	public:
		ScriptSystem();
		void Start(std::vector < std::shared_ptr<spic::GameObject >> entities);
		void Update(std::vector<std::shared_ptr<spic::GameObject>> entities);
	};
}