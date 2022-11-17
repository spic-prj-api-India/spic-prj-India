#include "GameEngine.hpp"
#include "EntityManager.hpp"
#include "Scene.hpp"
#include <map>
#include <regex>
#include <memory>
#include <mutex>

using namespace spic;

GameEngine* GameEngine::pinstance_{ nullptr };
std::mutex GameEngine::mutex_;

internal::EntityManager* entityManager = internal::EntityManager::GetInstance();
std::map<std::string, std::shared_ptr<Scene>> scenes;

GameEngine::GameEngine()
{}

GameEngine::~GameEngine()
{}

void LoadScene(std::shared_ptr<Scene> scene)
{
	entityManager->SetScene(scene);
}

void DestroyScene(bool forceDelete)
{
	entityManager->DestroyScene(forceDelete);
}

void SetActiveScene(std::string scene)
{
	auto it = scenes.find(scene);
	LoadScene(it->second);
}

std::weak_ptr<Scene> GetActiveScene()
{
	return entityManager->currentScene;
}

std::shared_ptr<Scene> GetSceneByName(std::string sceneName)
{
	auto it = scenes.find(sceneName);
	return it->second;
}


GameEngine* GameEngine::GetInstance()
{
	std::lock_guard<std::mutex> lock(mutex_);
	if (pinstance_ == nullptr)
	{
		pinstance_ = new GameEngine();
	}
	return pinstance_;
}
