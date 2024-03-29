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
#include <functional>

namespace spic::internal
{
	/**
	 * @brief Format: [](){return new Scene()}
	*/
	typedef std::function<spic::Scene*(void)> CreateSceneFunction;

	/**
	 * @brief Manages all entities and scenes
	*/
	class EntityManager
	{
	private:
		static EntityManager* pinstance_;
		static std::mutex mutex_;

		const int CustomSystemDefaultPriority;

		/**
		 * @brief Entities that are send to systems
		*/
		std::vector<std::shared_ptr<spic::GameObject>> entities;

		/**
		 * @brief Entities that need to be removed in next update
		*/
		std::vector<std::string> removeEntities;

		/**
		 * @brief Systems of engine
		*/
		std::map<int, std::vector<std::unique_ptr<spic::systems::ISystem>>> systems;

		/**
		 * @brief Registered scenes.
		 *			CreateSceneFunction format: [](){return new Scene()}
		*/
		std::map<std::string, CreateSceneFunction> scenes;

		/**
		 * @brief Current scene
		*/
		std::shared_ptr<Scene> scene;
	protected:
		/**
		 * @brief Calls the init method
		*/
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
		* @param name The name of the entity that will be removed
		*/
		void RemoveEntity(const std::string& name);

		/*
		* @brief Register scene.
		* @param sceneName This is the key in the scenes list.
		* @param scene Function that creates scene.
		*			Format: [](){return new Scene()}
		*/
		void RegisterScene(const std::string& sceneName, CreateSceneFunction scene);

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
		@brief Sets the current scene with entities.
		@param The sceneName of the scene that needs to be set.
		@details Triggers an exception if the name does not 
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
		std::string typeName = spic::helper_functions::type_helper::GetTypeName<T>();
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