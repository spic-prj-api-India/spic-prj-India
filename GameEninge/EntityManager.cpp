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

using namespace spic;
using namespace spic::internal;
using namespace spic::systems;

EntityManager* EntityManager::pinstance_{ nullptr };
std::mutex EntityManager::mutex_;

std::vector<std::shared_ptr<GameObject>> entities;
std::vector <std::pair<int, std::unique_ptr<ISystem>>> systems;

EntityManager::EntityManager()
{}

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
{}

void EntityManager::SetScene(std::shared_ptr<Scene> scene)
{
	entities.clear();
	for (auto& entity : scene->contents)
	{
		entities.push_back(entity);
	}
}

void EntityManager::DestroyScene(bool forceDelete)
{
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

void EntityManager::AddSystem(std::unique_ptr<systems::ISystem> system)
{}

void EntityManager::RemoveSystem(std::unique_ptr<systems::ISystem> system)
{}

void EntityManager::Update(int deltaTime)
{}

void EntityManager::Render()
{}