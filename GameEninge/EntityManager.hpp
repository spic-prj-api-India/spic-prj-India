#ifndef ENTITYMANAGER_H_
#define ENTITYMANAGER_H_

#include <map>
#include <regex>
#include <memory>
#include <mutex>
#include <vector>
#include <iostream>
#include "ISystem.hpp"
#include "Scene.hpp"

namespace spic::internal 
{
	class EntityManager
	{
	private:
		static EntityManager* pinstance_;
		static std::mutex mutex_;

		std::vector<std::shared_ptr<spic::GameObject>> entities;
		std::vector <std::pair<int, systems::ISystem>> systems;
	protected:
		EntityManager();
		~EntityManager();
	public:
		EntityManager(EntityManager& other) = delete;
		EntityManager(EntityManager&& other) = delete;
		void operator=(const EntityManager& other) = delete;
		EntityManager& operator=(EntityManager&& other) = delete;
		static EntityManager* GetInstance();

		std::weak_ptr<spic::Scene> currentScene;

		/*
		@brief Initialization of the class.
		*/
		void Init();

		/*
		@brief Set the current scene with entities.
		@param The scene to be set.
		*/
		void SetScene(std::shared_ptr<Scene> scene);

		/*
		@brief Destroy the current scene.
		@param forceDelete: Set to true to delete GameObjects with boolean "destroyOnLoad" as well.
		*/
		void DestroyScene(bool forceDelete);

		void AddSystem(systems::ISystem* system);

		void RemoveSystem(systems::ISystem* system);

		void Update(int deltaTime);

		void Render();

	};
}

#endif // ENTITYMANAGER_H_