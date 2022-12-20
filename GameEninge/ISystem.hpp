#ifndef ISYSTEM_H_
#define ISYSTEM_H_

#include <iostream>
#include <vector>
#include "Scene.hpp"

/**
 * @brief Contains the public interface for adding a new system
*/
namespace spic::systems 
{
	/**
	 * @brief The ISystem interface needs to be included before running the start method in game engine
	*/
	class ISystem
	{
	public:
		/**
		* @brief Is called when scene is loaded
		*/
		virtual void Start(std::vector<std::shared_ptr<spic::GameObject>>& entities, Scene& currentScene) = 0;

		/**
		* @brief Is called every tick
		*/
		virtual void Update(std::vector<std::shared_ptr<spic::GameObject>>& entities, Scene& currentScene) = 0;
	private:
	};
}

#endif // ISYSTEM_H_