#include "GameEngine.hpp"
#include "EntityManager.hpp"
#include "Scene.hpp"
#include <map>
#include <regex>
#include <memory>
#include <mutex>

namespace spic 
{
	GameEngine* GameEngine::pinstance_{ nullptr };
	std::mutex GameEngine::mutex_;

	GameEngine::GameEngine()
	{

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

	void GameEngine::SetActiveScene(std::string scene)
	{
		auto it = scenes.find(scene);
		LoadScene(it->second);
	}

	std::weak_ptr<Scene> GameEngine::GetActiveScene()
	{
		return entityManager->currentScene;
	}

	void GameEngine::LoadScene(std::weak_ptr<Scene> scene)
	{
		entityManager->SetScene(scene);
	}
}