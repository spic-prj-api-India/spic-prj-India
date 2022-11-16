#pragma once

#include <map>
#include <regex>
#include <memory>
#include <mutex>
#include <vector>
#include <iostream>
#include "ISystem.hpp"
#include "MapParser.hpp"
#include "Scene.hpp"

namespace spic::internal {

	class EntityManager
	{
	private:
		static EntityManager* pinstance_;
		static std::mutex mutex_;

	protected:
		EntityManager();
		~EntityManager();
	public:
		EntityManager(EntityManager& other) = delete;
		EntityManager(EntityManager&& other) noexcept = delete;
		void operator=(const EntityManager& other) = delete;
		EntityManager& operator=(EntityManager&& other) noexcept = delete;
		static EntityManager* GetInstance();

		std::vector<std::shared_ptr<spic::GameObject>> entities;
		std::vector <std::pair<int, ISystem*>> systems;
		std::weak_ptr<Scene> currentScene;
		std::unique_ptr<MapParser> tileParser;

		void SetScene(std::shared_ptr<Scene> scene)
		{
			for (auto& entity : scene->contents)
			{
				entities.push_back(entity);
			}
		}

		void DestroyScene(bool forceDelete)
		{
			if (forceDelete)
			{
				entities.clear();
			}
			else
			{
				for (auto& entity : entities)
				{
					if (entity->destroyOnLoad)
					{
						entities.erase(std::remove(entities.begin(), entities.end(), entity), entities.end());
					}
				}
			}
		}

		void AddSystem(ISystem* system);

		void RemoveSystem(ISystem* system);

		void Update(int deltaTime);

		void Render();

	};
}
