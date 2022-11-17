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

EntityManager* EntityManager::pinstance_{ nullptr };
std::mutex EntityManager::mutex_;

std::vector<std::shared_ptr<spic::GameObject>> entities;
std::vector <std::pair<int, ISystem*>> systems;
std::weak_ptr<Scene> currentScene;
std::unique_ptr<MapParser> tileParser;

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
{ 
	// Add required systems 
}

void EntityManager::SetScene(std::shared_ptr<Scene> scene)
{
	for (auto& entity : scene->contents)
	{
		entities.push_back(entity);
	}
	currentScene = scene;
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
			if (entity->destroyOnLoad_)
			{
				entities.erase(std::remove(entities.begin(), entities.end(), entity), entities.end());
			}
		}
	}
}

void EntityManager::AddSystem(ISystem* system)
{}

void EntityManager::RemoveSystem(ISystem* system)
{}

void EntityManager::Update(int deltaTime)
{}

void EntityManager::Render()
{}