#ifndef ENTITYMANAGER_H_
#define ENTITYMANAGER_H_

#include <map>
#include <memory>
#include <mutex>
#include <vector>
#include <iostream>
#include "ISystem.hpp"
#include "Scene.hpp"
#include "TypeHelper.hpp"

namespace spic::internal 
{
	class EntityManager
	{
	private:
		static EntityManager* pinstance_;
		static std::mutex mutex_;

		std::vector<std::shared_ptr<spic::GameObject>> entities;
		std::vector<std::pair<int, std::unique_ptr<spic::systems::ISystem>>> systems;
		std::shared_ptr<Scene> scene;
	protected:
		EntityManager();
		~EntityManager();
	public:
		EntityManager(EntityManager& other) = delete;
		EntityManager(EntityManager&& other) = delete;
		void operator=(const EntityManager& other) = delete;
		EntityManager& operator=(EntityManager&& other) = delete;
		static EntityManager* GetInstance();

		/*
		@brief Initialization of the class.
		*/
		void Init();

		/*
		@brief Sets the current scene with entities.
		@param The scene to be set.
		*/
		void SetScene(std::shared_ptr<Scene> scene);

		/*
		@brief Destroys the current scene.
		@param forceDelete: Set to true to delete GameObjects with boolean "destroyOnLoad = false" as well.
		*/
		void DestroyScene(bool forceDelete);

		/*
		@brief Use this class to add a (custom) system to the systems list.
		@param The (custom) system to be added.
		*/
		void AddSystem(std::unique_ptr<spic::systems::ISystem> system, int priority = 0);

		/*
		@brief Use this class to remove a (custom) system to the systems list. 
		@param The (custom) system to be removed.
		*/
		template <typename T>
		void RemoveSystem() {
			std::string typeName = GetTypeName<T>();
			systems.erase(std::remove_if(systems.begin(), systems.end(), [typeName](std::pair<int, std::unique_ptr<spic::systems::ISystem>> system) {
				return typeName == GetTypeName(system.second);
				}));
		}

		/*
		@brief The update function which updates the systems according to the specified DeltaTime.
		@param deltaTime: The Delta Time.
		*/
		void Update();

		/*
		@brief Calls the RendererSystem to render the entities and tilemap. 
		*/
		void Render();
	};
}

#endif // ENTITYMANAGER_H_