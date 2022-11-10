#ifndef SCRIPTSYSTEM_H_
#define SCRIPTSYSTEM_H_

#include "ISystem.hpp"

namespace systems {
	class ScriptSystem :
		public ISystem
	{
	public:
		ScriptSystem();

		void Start(std::vector < std::shared_ptr<spic::GameObject >> entities) const;
		void Update(std::vector<std::shared_ptr<spic::GameObject>> entities) const;
	};
}

#endif // SCRIPTSYSTEM_H_