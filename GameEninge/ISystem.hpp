#ifndef ISYSTEM_H_
#define ISYSTEM_H_

#include <iostream>
#include <vector>
#include "Scene.hpp"

namespace spic::systems 
{
	class ISystem
	{
	public:
		virtual void Update(std::vector<std::shared_ptr<spic::GameObject>>& entities, Scene& currentScene) = 0;
	private:
	};
}

#endif // ISYSTEM_H_