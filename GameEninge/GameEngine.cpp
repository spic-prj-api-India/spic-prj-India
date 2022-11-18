#include "GameEngine.hpp"
#include "EntityManager.hpp"

namespace spic {
	GameEngine* GameEngine::pinstance_{ nullptr };
	std::mutex GameEngine::mutex_;

	GameEngine::GameEngine()
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
}