#include "GameEngine.hpp"
#include "EntityManager.hpp"
#include "SDL2/SDL.h"
#include "Input.hpp"

namespace spic {
	GameEngine* GameEngine::pinstance_{ nullptr };
	std::mutex GameEngine::mutex_;

	GameEngine::GameEngine() : quit{ false }
	{
		_extensions;
	}

	GameEngine::~GameEngine()
	{}

	GameEngine* GameEngine::GetInstance()
	{
		std::lock_guard<std::mutex> lock(mutex_);
		if (pinstance_ == nullptr)
		{
			pinstance_ = new GameEngine();
		}
		return pinstance_;
	}

	void GameEngine::LoadScene(std::shared_ptr<Scene> scene)
	{
		spic::internal::EntityManager::GetInstance()->SetScene(scene);
	}

	void GameEngine::DestroyScene(bool forceDelete)
	{
		internal::EntityManager::GetInstance()->DestroyScene(forceDelete);
	}

	void GameEngine::Start()
	{
		const int FPS = 60;
		const int frameDelay = 1000 / FPS;

		Uint32 frameStart;
		int frameTime;

		while (!quit) {
			frameStart = SDL_GetTicks();

			internal::EntityManager::GetInstance()->Update();

			// make the program sleep for the alotted time so nothing occurs within the excess frames and we can efficiently use the computers processing power.
			frameTime = SDL_GetTicks() - frameStart;
			if (frameDelay > frameTime)
			{
				SDL_Delay(frameDelay - frameTime);
			}
		}
	}

	void GameEngine::Quit()
	{
		quit = true;
	}
}