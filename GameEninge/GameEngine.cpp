#include <codeanalysis\warnings.h>
#pragma warning( push )
#pragma warning ( disable : ALL_CODE_ANALYSIS_WARNINGS )
#include "SDL2/SDL.h"
#pragma warning( pop )
#include "GameEngine.hpp"
#include "EntityManager.hpp"
#include "Input.hpp"
#include "Renderer.hpp"

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

	void RegisterScene(const std::string& sceneName, std::shared_ptr<Scene> scene)
	{
		internal::EntityManager::GetInstance()->RegisterScene(sceneName, scene);
	}

	void SetActiveScene(const std::string& sceneName)
	{
		internal::EntityManager::GetInstance()->SetScene(sceneName);
	}

	void GameEngine::LoadScene(std::shared_ptr<Scene> scene)
	{
		spic::internal::EntityManager::GetInstance()->SetScene(scene);
	}

	void GameEngine::DestroyScene(bool forceDelete)
	{
		internal::EntityManager::GetInstance()->DestroyScene(forceDelete);
	}

	std::shared_ptr<Scene> GetActiveScene()
	{
		return internal::EntityManager::GetInstance()->GetScene();
	}

	std::shared_ptr<Scene> GetSceneByName(const std::string& sceneName)
	{
		return internal::EntityManager::GetInstance()->GetScene(sceneName);
	}

	void GameEngine::Start(const spic::window::WindowValues* values)
	{
		const int FPS = 60;
		const int frameDelay = 1000 / FPS;

		Uint32 frameStart;
		int frameTime;

		spic::internal::Rendering::Start(values);

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