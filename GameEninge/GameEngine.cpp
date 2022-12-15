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

	std::shared_ptr<spic::GameObject> GameEngine::CreateType(const std::string& typeName)
	{
		if (_types.count(typeName) == 0)
			throw std::exception("Type not registered.");
		return _types[typeName]();
	}

	void GameEngine::RegisterScene(const std::string& sceneName, std::shared_ptr<Scene> scene)
	{
		internal::EntityManager::GetInstance()->RegisterScene(sceneName, scene);
	}

	void GameEngine::LoadSceneByName(const std::string& sceneName)
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

	std::shared_ptr<Scene> GameEngine::GetActiveScene()
	{
		return internal::EntityManager::GetInstance()->GetScene();
	}

	std::shared_ptr<Scene> GameEngine::GetSceneByName(const std::string& sceneName)
	{
		return internal::EntityManager::GetInstance()->GetScene(sceneName);
	}

	void GameEngine::Start(const spic::window::WindowValues* values)
	{
		spic::internal::Rendering::Start(values);

		while (!quit) {
	
			internal::EntityManager::GetInstance()->Update();
		}
	}

	void GameEngine::Quit()
	{
		quit = true;
	}
}