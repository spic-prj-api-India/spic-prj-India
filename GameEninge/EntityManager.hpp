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

		const int CustomSystemDefaultPriority;

		std::vector<std::shared_ptr<spic::GameObject>> entities;
		std::map<int, std::vector<std::unique_ptr<spic::systems::ISystem>>> systems;
		std::map<std::string, std::shared_ptr<Scene>> scenes;
		std::shared_ptr<Scene> scene;
		std::string currentSceneName;
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
		* @brief Initialization of the class.
		*/
		void Init();

		/*
		* @brief Clears all variable members.
		*/
		void Reset();

		/*
		* @brief Gets entities that are currently loaded.
		* @return The current entities
		*/
		std::vector<std::shared_ptr<spic::GameObject>> GetEntities();

		/*
		* @brief Add entity.
		* @param entity The entity that will be added
		* @throws Throws if entity does not have a name
		*/
		void AddEntity(std::shared_ptr<spic::GameObject> entity);

		/*
		* @brief Add entity.
		* @param entity The entity that will be added
		*/
		void AddEntityAlsoToScene(const std::shared_ptr<spic::GameObject>& entity);
		/*
		* @brief Remove entity.
		* @param entity The entity that will be removed
		*/
		void RemoveEntity(const std::shared_ptr<spic::GameObject>& entity);

		/*
		* @brief Register scene.
		* @param The sceneName is the key in the scenes list.
		* @param The scene that will be registered in scenes list.
		*/
		void RegisterScene(const std::string& sceneName, std::shared_ptr<Scene> scene);

		/*
		* @brief Gets current scene.
		* @returns The current scene.
		*/
		std::shared_ptr<Scene> GetScene();

		/*
		* @brief Gets scene with name.
		* @param The sceneName of the scene.
		* @returns The scene with the given sceneName.
		*/
		std::shared_ptr<Scene> GetScene(const std::string& sceneName);

		/*
		* @brief Sets the current scene with entities.
		* @param The sceneName of the scene that needs to be set.
		*/
		void SetScene(const std::string& sceneName);

		/*
		* @brief Sets the current scene with entities.
		* @param The scene to be set.
		*/
		void SetScene(std::shared_ptr<Scene> scene);

		/*
		* @brief Destroys the current scene.
		* @param forceDelete: Set to true to delete GameObjects with boolean "destroyOnLoad = false" as well.
		*/
		void DestroyScene(bool forceDelete = false);

		/*
		* @brief Use this function to add a (custom) system to the systems list.
		* @param The (custom) system to be added.
		*/
		void AddSystem(std::unique_ptr<spic::systems::ISystem> system);

		/**
		 * @brief Calls an condition relating to the current entities list
		 * @param function 
		 * @return 
		*/
		bool CheckIfNameExists(const std::string& name) const;

		/*
		* @brief Use this function to remove a (custom) system to the systems list.
		* @param The (custom) system to be removed.
		*/
		template <typename T>
		void RemoveSystem();

		/*
		* @brief The update function which updates the systems according to the specified DeltaTime.
		* @param deltaTime: The Delta Time.
		*/
		void Update();

	private:
		/*
		* @brief Use this function to add a internal system to the systems list.
		* @param The (custom) system to be added.
		*/
		void AddInternalSystem(std::unique_ptr<spic::systems::ISystem> system, int priority = 0);
	};

	template <typename T>
	void EntityManager::RemoveSystem() {
		std::string typeName = spic::TypeHelper::GetTypeName<T>();
		for (auto& systemPair : systems) {
			auto& vec = systemPair.second;
			auto start_junk = std::remove_if(
				vec.begin(), vec.end(),
				[typeName](const auto& system) {
					std::string systemName = typeid(*system).name();
					std::string strippedName = std::regex_replace(systemName, std::regex("class "), "");
					return typeName == strippedName;
				});
			vec.erase(start_junk, vec.end());
		}
	}
}

#endif // ENTITYMANAGER_H_