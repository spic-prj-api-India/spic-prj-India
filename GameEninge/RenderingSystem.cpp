#include "RenderingSystem.hpp"

namespace spic::internal::systems {
	RenderingSystem::RenderingSystem() 
	{
		SDL_Window* window = SDL_CreateWindow("window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 500, SDL_WINDOW_RESIZABLE);
	}

	RenderingSystem::~RenderingSystem()
	{
		SDL_DestroyWindow(window);
		SDL_Quit();
	}

	void RenderingSystem::Start(std::vector<std::shared_ptr<spic::GameObject>>& entities)
	{}

	void RenderingSystem::Update(std::vector<std::shared_ptr<spic::GameObject>>& entities, Scene& currentScene)
	{}
}