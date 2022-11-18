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
		std::vector<std::pair<int, std::unique_ptr<systems::ISystem>>> systems;

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
		void AddSystem(std::unique_ptr<systems::ISystem> system);

		/*
		@brief Use this class to remove a (custom) system to the systems list. 
		@param The (custom) system to be removed.
		*/
		void RemoveSystem(std::unique_ptr<systems::ISystem> system);

		/*
		@brief The update function which updates the systems according to the specified DeltaTime.
		@param deltaTime: The Delta Time.
		*/
		void Update(int deltaTime);

		/*
		@brief Calls the RendererSystem to render the entities and tilemap. 
		*/
		void Render();

	};
}

#endif // ENTITYMANAGER_H_