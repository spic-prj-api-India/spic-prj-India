#include <map>
#include <regex>
#include <memory>
#include <mutex>
#include <vector>
#include <iostream>
#include "EntityManager.hpp"
#include "ISystem.hpp"
#include "MapParser.hpp"
#include "InputSystem.hpp"
#include "PhysicsSystem.hpp"
#include "RenderingSystem.hpp"
#include "DataSystem.hpp"
#include "AudioManager.hpp"
#include "NetworkingReceiveSystem.hpp"
#include "NetworkingSendSystem.hpp"

using namespace spic;
using namespace spic::internal;
using namespace spic::systems;

EntityManager* EntityManager::pinstance_{ nullptr };
std::mutex EntityManager::mutex_;

EntityManager::EntityManager() : CustomSystemDefaultPriority{ 1 }, scene{ nullptr }
{
	Init();
}

EntityManager::~EntityManager()
{}

EntityManager* EntityManager::GetInstance()
{
	std::lock_guard<std::mutex> lock(mutex_);
	if (pinstance_ == nullptr)
	{
		pinstance_ = new EntityManager();
	}
	return pinstance_;
}

void EntityManager::Init()
{
	std::unique_ptr<systems::InputSystem> inputSystem = std::make_unique<systems::InputSystem>();
	std::unique_ptr<systems::PhysicsSystem> physicsSystem = std::make_unique<systems::PhysicsSystem>();
	std::unique_ptr<systems::RenderingSystem> renderingSystem = std::make_unique<systems::RenderingSystem>();
	std::unique_ptr<systems::DataSystem> dataSystem = std::make_unique<systems::DataSystem>();
	std::unique_ptr<systems::NetworkingReceiveSystem> networkRecieve = std::make_unique<systems::NetworkingReceiveSystem>();
	std::unique_ptr<systems::NetworkingSendSystem> networkSend = std::make_unique<systems::NetworkingSendSystem>();
	AddInternalSystem(std::move(networkRecieve), 0);
	AddInternalSystem(std::move(inputSystem), 1);
	AddInternalSystem(std::move(physicsSystem), 2);
	AddInternalSystem(std::move(dataSystem), 3);
	AddInternalSystem(std::move(networkSend), 4);
	AddInternalSystem(std::move(renderingSystem), 5);
}

void EntityManager::Reset()
{
	entities.clear();
	systems.clear();
	scenes.clear();
	scene = nullptr;
}

std::vector<std::shared_ptr<spic::GameObject>> EntityManager::GetEntities() {
	return entities;
}

void EntityManager::AddEntity(const std::shared_ptr<spic::GameObject>& entity)
{
	entities.push_back(entity);
}

void spic::internal::EntityManager::AddEntityAlsoToScene(const std::shared_ptr<spic::GameObject>& entity)
{
	AddEntity(entity);
	scene->AddContent(entity);
}

void EntityManager::RemoveEntity(const std::shared_ptr<spic::GameObject> entity) {
	entities.erase(
		std::remove(entities.begin(), entities.end(), entity),
		entities.end());
}

void EntityManager::RegisterScene(const std::string& sceneName, std::shared_ptr<Scene> scene)
{
	if (scenes.count(sceneName))
		throw std::exception("Scene with this name already exists.");
	scenes[sceneName] = scene;
}

std::shared_ptr<Scene> EntityManager::GetScene()
{
	return scene;
}

std::shared_ptr<Scene> EntityManager::GetScene(const std::string& sceneName)
{
	if (!scenes.count(sceneName))
		return nullptr;
	return scenes[sceneName];
}

void EntityManager::SetScene(const std::string& sceneName)
{
	if (!scenes.count(sceneName))
		throw std::exception("Scene does not exist.");

	if (currentSceneName != sceneName)
	{
		scene = scenes[sceneName];
		currentSceneName = sceneName;
		SetScene(scene);
	}
}

void EntityManager::SetScene(std::shared_ptr<Scene> newScene)
{
	DestroyScene();
	scene = newScene;
	entities.clear();
	const TileMap* tileMap = scene->TileMap();
	if (tileMap != nullptr) {
		for (auto& entity : scene->TileMap()->CollisionEntities()) {
			entities.push_back(entity);
		}
	}
	for (auto& entity : scene->Contents())
	{
		entities.push_back(entity);
	}
	for (const auto& systemsMap : systems)
	{
		for (const auto& system : systemsMap.second)
		{
			system->Start(entities, *scene);
		}
	}

	spic::internal::audio::AudioManager::GetInstance()->Reset();

	for (auto& entity : entities)
	{
		if (entity->Active())
			entity->Active(true);
	}
}

void EntityManager::DestroyScene(bool forceDelete)
{
	scene = nullptr;
	if (forceDelete)
	{
		entities.clear();
	}
	else
	{
		for (auto& entity : entities)
		{
			if (!entity->DontDestroyOnLoad())
			{
				entities.erase(std::remove(entities.begin(), entities.end(), entity), entities.end());
			}
		}
	}
}

void EntityManager::AddSystem(std::unique_ptr<spic::systems::ISystem> system)
{
	if (!systems.count(CustomSystemDefaultPriority))
	{
		systems[CustomSystemDefaultPriority];
	}
	systems[CustomSystemDefaultPriority].emplace_back(std::move(system));
}

bool spic::internal::EntityManager::CheckIfNameExists(const std::string& name) const
{
	for (auto& s : scenes)
	{
		for (auto& entity : s.second->Contents())
		{
			auto children = entity->GetChildren();
			if (spic::GameObject::CheckIfNameExists(children, name))
				return true;
		}
	}
	
	return false;
}

void EntityManager::AddInternalSystem(std::unique_ptr<spic::systems::ISystem> system, int priority)
{
	if (!systems.count(priority))
	{
		systems[priority];
	}
	systems[priority].emplace_back(std::move(system));
}

void EntityManager::Update()
{
	for (const auto& systemsMap : systems)
	{
		for (const auto& system : systemsMap.second)
		{
			system->Update(entities, *scene);
		}
	}
}