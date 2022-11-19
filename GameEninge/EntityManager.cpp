#include "EntityManager.hpp"
#include <map>
#include <regex>
#include <memory>
#include <mutex>
#include <vector>
#include <iostream>
#include "ISystem.hpp"
#include "MapParser.hpp"
#include "Scene.hpp"
#include "InputSystem.hpp"
#include "PhysicsSystem.hpp"
#include "ScriptSystem.hpp"
#include "RenderingSystem.hpp"

using namespace spic;
using namespace spic::internal;

EntityManager* EntityManager::pinstance_{ nullptr };
std::mutex EntityManager::mutex_;

std::vector<std::shared_ptr<GameObject>> entities;
std::vector <std::pair<int, std::unique_ptr<spic::systems::ISystem>>> systems;

EntityManager::EntityManager()
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
	AddSystem(std::move(inputSystem));
	AddSystem(std::move(physicsSystem));
	AddSystem(std::move(scriptSystem));
	AddSystem(std::move(renderingSystem));
}

void EntityManager::SetScene(std::shared_ptr<Scene> newScene)
{
	scene = newScene;
	entities.clear();
	for (auto& entity : newScene->Contents())
	{
		entities.push_back(entity);
	}
	for (const auto& system : systems)
		system.second->Start(entities);
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

void EntityManager::AddSystem(std::unique_ptr<spic::systems::ISystem> system, int priority)
{
	auto prioritySystem = std::make_pair(priority, std::move(system));
	systems.emplace_back(std::move(prioritySystem));
}

void EntityManager::Update()
{
	for (const auto& system : systems)
		system.second->Update(entities, *scene);
}

void EntityManager::Render()
{}