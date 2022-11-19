#ifndef RENDERINGSYSTEM_H_
#define RENDERINGSYSTEM_H_

#include "ISystem.hpp"
#include "SDL2/SDL.h"

/**
* @brief A system that calls the Start and Update method in scripts of entities
*/
namespace spic::internal::systems {
	class RenderingSystem :
		public spic::systems::ISystem
	{
	public:
		RenderingSystem();
		~RenderingSystem();
		RenderingSystem(RenderingSystem& other) = delete;
		RenderingSystem(RenderingSystem&& other) = delete;
		void operator=(const RenderingSystem& other) = delete;
		RenderingSystem& operator=(RenderingSystem&& other) = delete;

		/**
		* @brief Initiliazes system
		* @spicapi
		*/
		void Start(std::vector<std::shared_ptr<spic::GameObject>>& entities) override;

		/**
		* @brief Renders all entities in current scene
		* @spicapi
		*/
		void Update(std::vector<std::shared_ptr<spic::GameObject>>& entities, Scene& currentScene) override;
	private:
		SDL_Window* window;
	};
}

#endif // RENDERINGSYSTEM_H_