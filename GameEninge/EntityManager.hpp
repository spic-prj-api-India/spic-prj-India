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

	/*
	* @brief The main entity manager class. It has multiple functions to update the systems, scenes and entities.
	*/
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

		void AddSystem(ISystem* system);

		void RemoveSystem(ISystem* system);

		void Update(int deltaTime);

		void Render();
	};
}
