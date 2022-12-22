#include "GameEngine.hpp"
#include "EntityManager.hpp"
#include "Input.hpp"
#include "Renderer.hpp"
#include "InternalTime.hpp"
#include "DataHandler.hpp"

namespace spic 
{
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
			return std::make_shared<GameObject>();

		return _types[typeName]();
	}

	void GameEngine::RegisterScene(const std::string& sceneName, std::function<spic::Scene* ()> scene)
	{
		internal::EntityManager::GetInstance()->RegisterScene(sceneName, scene);
	}

	void GameEngine::LoadSceneByName(const std::string& sceneName)
	{
		internal::EntityManager::GetInstance()->SetScene(sceneName);
	}

	void GameEngine::LoadScene(std::shared_ptr<Scene> scene)
	{
		spic::internal::EntityManager::GetInstance()->SetScene(std::move(scene));
	}

	void GameEngine::SaveScene(const std::string& fileName)
	{
		DataHandler dataHandler = DataHandler(fileName);
		dataHandler.AddScene(spic::internal::EntityManager::GetInstance()->GetEntities());
		dataHandler.Save();
	}

	void GameEngine::LoadSceneBySaveFile(std::shared_ptr<Scene> scene, const std::string& fileName)
	{
		spic::internal::EntityManager::GetInstance()->SetScene(scene);
		DataHandler dataHandler = DataHandler(fileName);
		dataHandler.LoadScene(spic::internal::EntityManager::GetInstance()->GetEntities());
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
		return std::move(internal::EntityManager::GetInstance()->GetScene(sceneName));
	}

	void GameEngine::Start()
	{
		spic::internal::Rendering::Start();

		while (!quit) 
		{
			using namespace spic::internal::time;
			InternalTime::BeginFrame();
	
			internal::EntityManager::GetInstance()->Update();

			InternalTime::EndFrame();

			InternalTime::Delay();
		}
	}

	void GameEngine::Quit()
	{
		quit = true;
	}
}