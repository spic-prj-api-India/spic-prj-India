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
		/**
		* @brief Is called when scene is loaded
		* @spicapi
		*/
		virtual void Start(std::vector<std::shared_ptr<spic::GameObject>>& entities) = 0;

		/**
		* @brief Is called every tick
		* @spicapi
		*/
		virtual void Update(std::vector<std::shared_ptr<spic::GameObject>>& entities, Scene& currentScene) = 0;
	private:
	};
}

#endif // ISYSTEM_H_