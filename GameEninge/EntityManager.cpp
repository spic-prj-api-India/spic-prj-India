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
#include "ScriptSystem.hpp"
#include "AISystem.hpp"
#include "RenderingSystem.hpp"
#include "AudioManager.hpp"

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
	std::unique_ptr<systems::ScriptSystem> scriptSystem = std::make_unique<systems::ScriptSystem>();
	std::unique_ptr<systems::RenderingSystem> renderingSystem = std::make_unique<systems::RenderingSystem>();
	std::unique_ptr<systems::AISystem> aiSystem = std::make_unique<systems::AISystem>();
	AddInternalSystem(std::move(inputSystem), 0);
	AddInternalSystem(std::move(physicsSystem), 1);
	AddInternalSystem(std::move(aiSystem), 1);
	AddInternalSystem(std::move(scriptSystem), 1);
	AddInternalSystem(std::move(renderingSystem), 2);
}

void EntityManager::Reset()
{
	entities.clear();
	systems.clear();
	scenes.clear();
	scene = nullptr;
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
	DestroyScene();
	scene = scenes[sceneName];
	entities.clear();
	for (auto& entity : scene->Contents())
	{
		entities.push_back(entity);
	}
	for (const auto& systemsMap : systems)
	{
		for (const auto& system : systemsMap.second)
		{
			system->Start(entities);
		}
	}
}

std::vector<std::shared_ptr<spic::GameObject>> EntityManager::GetEntities() {
	return entities;
}

void EntityManager::AddEntity(const std::shared_ptr<spic::GameObject>& entity)
{
	entities.push_back(entity);
}

void EntityManager::RemoveEntity(const std::shared_ptr<spic::GameObject>& entity) {
	entities.erase(
		std::remove(entities.begin(), entities.end(), entity),
		entities.end());
}

void EntityManager::SetScene(std::shared_ptr<Scene> newScene)
{
	DestroyScene();
	scene = newScene;
	entities.clear();
	TileMap* tileMap = scene->TileMap();
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
			system->Start(entities);
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

void EntityManager::Render()
{}